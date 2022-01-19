#include "rt.h"
#include "color.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "random.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "diffuse_light.h"

#include "image.h"
#include "texture/checker.h"
#include "texture/image_texture.h"
#include "texture/modifiers.h"

using std::make_shared;


Color RayColor(const Ray& ray,
               const Color& background,
               const Hittable& world,
               int depth)
{
    HitRecord hit;

    // Check if we reached the ray bounce limit, in which case
    // no more light is gathered.
    if (depth <= 0)
    {
        return {0, 0, 0};
    }

    // If ray hits nothing, return the background color
    if (!world.Hit(ray, 0.001, INFINITY, hit))
    {
        return background;
    }

    // Calculate emitted light from hit
    const auto emitted = hit.material->Emitted(hit.u, hit.v, hit.p);

    Ray scattered;
    Color attenuation;

    if (!hit.material->Scatter(ray, hit, attenuation, scattered))
    {
        // If ray was not scattered, return the emitted light.
        return emitted;
    }

    // Gather the color of emitted light, the scattered ray,
    // and factor out absorbed light.
    return emitted + attenuation * RayColor(
        scattered,
        background,
        world,
        depth-1);
}

int main()
{
    // Dimensions
    const auto aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = static_cast<int>(width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    const auto lookfrom   = Point3(0, 1, 3);
    const auto lookat     = Point3(0, 0, -1);
    const auto focus_dist = (lookfrom-lookat).length();
    const auto aperture   = 0.05;

    // Camera
    const auto camera = Camera(lookfrom,
                               lookat,
                               Vec3(0, 1, 0),
                               40.0,
                               aspect_ratio,
                               aperture,
                               focus_dist);

    // Background
    const auto bg = Color(0, 0, 0);

    // Images
    const auto earthimg = make_shared<Image>("images/earth.jpg");
    const auto earthmap = make_shared<ImageTexture>(earthimg)
        | offset_u{0.3};

    const auto sunset = make_shared<Image>("images/sunset.jpg");
    const auto skymap = make_shared<ImageTexture>(sunset)
        | flip_v()
        | offset_u{0.5};

    // Materials
    const auto ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    const auto metal  = make_shared<Metal>(Color(0.5, 0.5, 0.5), 0.1);
    const auto earth  = make_shared<Lambertian>(earthmap);
    const auto light  = make_shared<DiffuseLight>(Color(10, 10, 10));
    const auto sky    = make_shared<DiffuseLight>(skymap);

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1.0),    0.5, metal));
    world.add(make_shared<Sphere>(Point3(0, 0,  0.0), -100.0, sky));

    // Create PPM image
    // Header
    std::cout << "P3\n"
              << width << ' ' << height << '\n'
              << "255\n";

    for (int y = height - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;

        for (int x = 0; x < width; ++x)
        {
            Color pixel;

            for (int sample = 0; sample < samples_per_pixel; ++sample)
            {
                // Choose a random point inside the pixel
                const auto u = (static_cast<double>(x) + random_double()) / (width - 1);
                const auto v = (static_cast<double>(y) + random_double()) / (height - 1);

                // Shoot ray into world
                const auto ray = camera.GetRay(u, v);

                // Accumulate color for each sample
                pixel += RayColor(ray, bg, world, max_depth);
            }

            // Write pixel
            write_color(std::cout, pixel, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
