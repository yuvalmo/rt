#pragma once

#include <vec3.h>

#include <string>
#include <memory>


class Image
{
public:
    Image(std::string filepath);

public:
    /**
     * Get color at uv coordinate.
     */
    Color GetColor(double u, double v) const;

private:
    std::unique_ptr<unsigned char> m_pixels;
    int m_width;
    int m_height;
    int m_bytes_per_scanline;
};
