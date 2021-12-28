/**
 * Abstraction class for hittable objects.
 */
#pragma once

#include "ray.h"


struct HitRecord
{
    Point3 p;         // Point of hit
    Vec3 normal;      // Surface normal
    double t;         // t for which the ray hits
    bool front_face;  // Whether the ray hit a front or back face

    inline void SetFaceNormal(const Ray& ray, const Vec3& outward_normal)
    {
        front_face = dot(ray.Direction(), outward_normal) < 0.0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    /**
     * Return whether the ray will hit this object.
     *
     * @return True if hit, false otherwise.
     *         Details will be stored in o_rec.
     */
    virtual bool Hit(const Ray& ray,
                     double t_min,
                     double t_max,
                     HitRecord& o_rec) const = 0;
};
