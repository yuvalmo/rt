#include "color.h"
#include "ray.h"
#include "vec3.h"


Color RayColor(const Ray& ray)
{
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
    const int width = 16;
    const int height = static_cast<int>(width / aspect_ratio);

    // Camera
    const auto viewport_height = 2.0;
    const auto viewport_width = aspect_ratio * viewport_height;
    const auto focal_length = 1.0;
    const auto origin = Point3(0, 0, 0);

    // Axis
    const auto horizontal = Vec3(viewport_width, 0, 0); // X axis vector
    const auto vertical = Vec3(0, viewport_height, 0);  // Y axis vector

    // Viewport
    const auto lower_left_corner = origin
        - Vec3(0, 0, focal_length)  // Move onto viewport plane
        - horizontal / 2            // Move left
        - vertical / 2;             // Move down

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
            const auto u = static_cast<double>(x) / (width - 1);
            const auto v = static_cast<double>(y) / (height - 1);

            // Calculate point on viewport
            const auto p = lower_left_corner
                + u * horizontal // Translate across x axis
                + v * vertical   // Translate across y axis
                - origin;        // Follow camera

            // Shoot ray into world
            const auto ray = Ray(origin, p);

            // Write pixel
            write_color(std::cout, RayColor(ray));
        }
    }

    std::cerr << "\nDone.\n";
}
