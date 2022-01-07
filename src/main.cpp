#include "rt.h"
#include "color.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "random.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "math_utils.h"

using std::make_shared;


Color RayColor(const Ray& ray, const Hittable& world, int depth)
{
    HitRecord hit;

    // Check if we reached the ray bounce limit, in which case
    // no more light is gathered.
    if (depth <= 0)
    {
        return {0, 0, 0};
    }

    // Check for hits
    if (world.Hit(ray, 0.001, INFINITY, hit))
    {
        Ray scattered;
        Color attenuation;

        if (hit.material->Scatter(ray, hit, attenuation, scattered))
        {
            // Gather the color of the scattered ray, and factor out
            // absorbed light.
            return attenuation * RayColor(scattered, world, depth-1);
        }

        // Light was fully absorbed
        return {0, 0, 0};
    }

    // Normalize vector to [-1 < y < 1]
    const auto unit_direction = unit_vector(ray.Direction());

    // Scale to [0 < y < 1]
    const auto t = 0.5 * (unit_direction.y() + 1.0);

    // Gradient between these two colors
    const auto white = Color(1.0, 1.0, 1.0);
    const auto blue  = Color(0.5, 0.7, 1.0);

    return (1.0-t)*white + t*blue;
}

int main()
{
    // Dimensions
    const auto aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = static_cast<int>(width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    const auto lookfrom   = Point3(3, 3, 2);
    const auto lookat     = Point3(0, 0, -1);
    const auto focus_dist = (lookfrom-lookat).length();

    // Camera
    const auto camera = Camera(lookfrom,
                               lookat,
                               Vec3(0, 1, 0),
                               20.0,
                               aspect_ratio,
                               focus_dist);

    // Materials
    const auto mat_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    const auto mat_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    const auto mat_left   = make_shared<Dielectric>(1.5);
    const auto mat_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    // World
    HittableList world;
    world.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, mat_ground));
    world.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, mat_center));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, mat_left));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, mat_left));
    world.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, mat_right));

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
                pixel += RayColor(ray, world, max_depth);
            }

            // Write pixel
            write_color(std::cout, pixel, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
