/**
 * Dielectric (transparent, glass-like) material.
 */
#pragma once

#include "material.h"

class Dielectric : public Material
{
public:
    Dielectric(double index_of_refraction);

    bool Scatter(const Ray& ray,
                 const HitRecord& hit,
                 Color& o_attenuation,
                 Ray& o_scattered) const override;

private:
    // Index of Refraction
    double m_ir;
};

