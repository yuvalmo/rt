/**
 * Class representing ray of light.
 */
#pragma once

#include "vec3.h"

class Ray
{
public:
    Ray() = default;
    Ray(const Point3& origin, const Vec3& direction);

    /**
     * Getters
     */
    Point3 Origin() const { return m_origin; }
    Vec3 Direction() const { return m_direction; }

    /**
     * Get point along ray.
     */
    Point3 At(double t) const;

private:
    Point3 m_origin;
    Vec3 m_direction;
};
