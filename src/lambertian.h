/**
 * Lambertian material with "perfect"
 * diffuse reflection.
 */
#pragma once

#include "material.h"


class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo);

    bool Scatter(const Ray& ray,
                 const HitRecord& hit,
                 Color& o_attenuation,
                 Ray& o_scattered) const override;

private:
    /**
     * Albedo is a factor in the [0,1] range that indicates
     * how much a surface reflects light.
     *
     * Examples:
     *  0 is fully absorbent ("black body").
     *  1 is fully reflective.
     */
    Color m_albedo;
};
