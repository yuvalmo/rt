/**
 * Metal reflective material.
 */
#pragma once

#include "material.h"


class Metal : public Material
{
public:
    Metal(const Color& albedo, double fuzz);

    bool Scatter(const Ray& ray,
                 const HitRecord& hit,
                 Color& o_attenuation,
                 Ray& o_scattered) const override;

private:
    Color m_albedo;
    double m_fuzz;
};
