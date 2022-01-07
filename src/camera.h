/**
 * Camera class.
 */
#pragma once

#include "ray.h"

class Camera
{
public:
    Camera(Point3 lookfrom,
           Point3 lookat,
           Vec3 vup,
           double vfov,
           double aspect_ratio,
           double focus_dist);

    /**
     * Get ray pointing at pixel at (u, v).
     */
    Ray GetRay(double u, double v) const;

private:
    Point3 m_origin;
    Point3 m_lower_left_corner;
    Vec3   m_horizontal;
    Vec3   m_vertical;
    Vec3   m_cz;
    Vec3   m_cx;
    Vec3   m_cy;
};
