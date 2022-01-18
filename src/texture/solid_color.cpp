#include "solid_color.h"

SolidColor::SolidColor(Color c)
    : m_color(c)
{
}

SolidColor::SolidColor(double red, double green, double blue)
    : m_color(red, green, blue)
{
}

Color SolidColor::Value(double, double, const Point3&) const
{
    return m_color;
}
