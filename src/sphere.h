/**
 * Sphere hittable object
 */
#pragma once

#include "hittable.h"

class Sphere : public Hittable
{
public:
    Sphere() = default;
    Sphere(Point3 center, double radius);

    bool Hit(const Ray& ray,
             double t_min,
             double t_max,
             HitRecord& o_rec) const override;

private:
    Point3 m_center;
    double m_radius;
};
