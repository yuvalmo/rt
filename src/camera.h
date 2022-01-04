/**
 * Camera class.
 */
#pragma once

#include "ray.h"

class Camera
{
public:
    Camera(double vfov,
           double aspect_ratio);

    /**
     * Get ray pointing at pixel at (u, v).
     */
    Ray GetRay(double u, double v) const;

private:
    Point3 m_origin;
    Point3 m_lower_left_corner;
    Vec3   m_horizontal;
    Vec3   m_vertical;
};
