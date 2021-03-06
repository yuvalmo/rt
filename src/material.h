/**
 * Material abstract class.
 */
#pragma once

#include <hittable.h>
#include <ray.h>


class Material
{
public:
    virtual ~Material() = default;

    /**
     * Scatter the hitting ray and produce an incident
     * ray.
     *
     * @param ray            Hitting ray
     * @param hit            Hit details
     * @param o_attenuation  How much the ray should be attenuated
     * @param o_scattered    New incident ray
     *
     * @return true if ray was scattered.
     *         false if ray was absorbed.
     */
    virtual bool Scatter(const Ray& ray,
                         const HitRecord& hit,
                         Color& o_attenuation,
                         Ray& o_scattered) const = 0;

    /**
     * Return how much light is emitted from the material's
     * surface in a given coordinate.
     *
     * A material emits no light by default.
     */
    virtual Color Emitted(double u,
                          double v,
                          const Point3& p) const
    {
        return {0, 0, 0};
    }
};
