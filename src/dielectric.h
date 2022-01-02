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
    static bool ShouldReflect(double cos_theta,
                              double sin_theta,
                              double refraction_ratio);
    /**
     * Calculate the ratio of reflected light, according to schlick's
     * approximation.
     *
     * @param cos_theta  Cosine of incoming ray with surface normal.
     * @param ref_idx    Refraction ratio.
     */
    static double Reflectance(double cos_theta, double ref_idx);

private:
    // Index of Refraction
    double m_ir;
};

