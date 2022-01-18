#pragma once

#include "texture.h"

/**
 * A texture whose color is the same in all coordinates.
 */
class SolidColor : public Texture
{
public:
    SolidColor(Color c);
    SolidColor(double red, double green, double blue);

public:
    Color Value(double u, double v, const Point3& p) const override;

private:
    Color m_color;
};
