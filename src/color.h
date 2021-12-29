/**
 * Color utilities.
 */
#pragma once

#include "vec3.h"

#include <algorithm>
#include <cmath>
#include <iostream>

void write_color(std::ostream& os, Color pixel_color, int samples_per_pixel)
{
    // TODO: Try passing color by non-const ref

    const double COLOR_MAX = 256;

    // Average the samples
    const auto c = pixel_color / samples_per_pixel;

    // Gamma-correct for gamma = 2.
    auto r = std::sqrt(c.x());
    auto g = std::sqrt(c.y());
    auto b = std::sqrt(c.z());

    // Convert to [0,255] range. The clamp is to pull 256
    // back into the wanted range.
    r = COLOR_MAX * std::clamp(r, 0.0, 0.999);
    g = COLOR_MAX * std::clamp(g, 0.0, 0.999);
    b = COLOR_MAX * std::clamp(b, 0.0, 0.999);

    os << static_cast<int>(r) << ' '
       << static_cast<int>(g) << ' '
       << static_cast<int>(b) << '\n';
}
