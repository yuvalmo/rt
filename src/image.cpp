#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <algorithm>

const auto BYTES_PER_PIXEL = 3;

Image::Image(std::string filepath)
    : m_pixels(),
      m_width(0),
      m_height(0),
      m_bytes_per_scanline(0)
{
    auto components_per_pixel = BYTES_PER_PIXEL;

    const auto data = stbi_load(filepath.c_str(),
                                &m_width,
                                &m_height,
                                &components_per_pixel,
                                components_per_pixel);

    if (!data)
    {
        std::cerr << "Error: failed loading texture image "
                  << filepath << ".\n";
    }
    else
    {
        m_pixels.reset(data);
        m_bytes_per_scanline = BYTES_PER_PIXEL * m_width;
    }
}

Color Image::GetColor(double u, double v) const
{
    // Return cyan if image was not found, to help debugging.
    if (m_pixels == nullptr)
        return {0, 1, 1};

    // Clamp uv coordinates to [0, 1]
    u = std::clamp(u, 0.0, 1.0);
    v = 1.0 - std::clamp(v, 0.0, 1.0); // Flip V to image coordinates

    auto i = static_cast<int>(u * m_width);
    auto j = static_cast<int>(v * m_height);

    // Clamp pixel coordinates
    if (i >= m_width)  i = m_width-1;
    if (j >= m_height) j = m_height-1;

    const auto pixel = m_pixels.get()
        + j * m_bytes_per_scanline  // Get row
        + i * BYTES_PER_PIXEL;      // Get column

    return {
        pixel[0] / 255.0,
        pixel[1] / 255.0,
        pixel[2] / 255.0
    };
}
