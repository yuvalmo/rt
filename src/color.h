/**
 * Color utilities.
 */
#pragma once

#include "vec3.h"
#include <iostream>

void write_color(std::ostream& os, const Color& pixel_color)
{
    const double COLOR_MAX = 255.999;

    os << static_cast<int>(COLOR_MAX * pixel_color.x()) << ' '
       << static_cast<int>(COLOR_MAX * pixel_color.y()) << ' '
       << static_cast<int>(COLOR_MAX * pixel_color.z()) << '\n';
}
