#include <iostream>

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
            const auto r = static_cast<double>(x) / (width - 1);
            const auto g = static_cast<double>(y) / (height - 1);
            const auto b = 0.25;

            // Colors
            const int ir = static_cast<int>(255.999 * r);
            const int ig = static_cast<int>(255.999 * g);
            const int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr << "\nDone.\n";
}
