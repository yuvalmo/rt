/**
 * Color utilities.
 */
#pragma once

#include "vec3.h"

#include <iostream>
#include <algorithm>

void write_color(std::ostream& os, Color pixel_color, int samples_per_pixel)
{
    // TODO: Try passing color by non-const ref

    const double COLOR_MAX = 256;

    // Average the samples
    const auto c = pixel_color / samples_per_pixel;

    // Convert to [0,255] range. The clamp is to pull 256
    // back into the wanted range.
    const auto r = COLOR_MAX * std::clamp(c.x(), 0.0, 0.999);
    const auto g = COLOR_MAX * std::clamp(c.y(), 0.0, 0.999);
    const auto b = COLOR_MAX * std::clamp(c.z(), 0.0, 0.999);

    os << static_cast<int>(r) << ' '
       << static_cast<int>(g) << ' '
       << static_cast<int>(b) << '\n';
}
