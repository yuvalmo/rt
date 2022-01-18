/**
 * Sphere hittable object
 */
#pragma once

#include <hittable.h>

class Sphere : public Hittable
{
public:
    Sphere() = default;
    Sphere(Point3 center, double radius, MaterialPtr material);

    bool Hit(const Ray& ray,
             double t_min,
             double t_max,
             HitRecord& o_rec) const override;

private:
    /**
     * Calculate uv coordinates for a given point on the surface.
     *
     * @param p     A point on the surface of a unit sphere.
     * @param o_u   Angle [0, 1] around Y axis starting from X=-1
     * @param o_v   Angle [0, 1] from Y=-1 to Y=+1.
     */
    static void get_uv(const Point3& p,
                       double& o_u,
                       double& o_v);

private:
    Point3 m_center;
    double m_radius;
    MaterialPtr m_material;
};
