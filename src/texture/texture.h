#pragma once

#include <vec3.h>


class Texture
{
public: 
    virtual ~Texture() = default;

    /**
     * Get color of texture at the given coordinates.
     */
    virtual Color Value(double u, double v, const Point3& p) const = 0;
};
