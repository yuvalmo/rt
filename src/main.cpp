#include "vec3.h"
#include "color.h"

int main()
{
    // Dimensions
    const int width = 256;
    const int height = 256;

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
            // Factor between 0 and 1
            Color pixel{
                static_cast<double>(x) / (width - 1),
                static_cast<double>(y) / (height - 1),
                0.25
            };

            write_color(std::cout, pixel);
        }
    }

    std::cerr << "\nDone.\n";
}
