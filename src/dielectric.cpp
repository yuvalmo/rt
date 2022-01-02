#include "dielectric.h"
#include <cmath>


Dielectric::Dielectric(double index_of_refraction)
    : m_ir(index_of_refraction)
{}

bool Dielectric::Scatter(const Ray& ray,
                         const HitRecord& hit,
                         Color& o_attenuation,
                         Ray& o_scattered) const
{
    const auto uv = unit_vector(ray.Direction());

    // Angles
    const double cos_theta = fmin(dot(-uv, hit.normal), 1.0);
    const double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    // The ratio is old_ior / new_ior. For that, we need to know
    // if the ray is entering the surface or exiting it.
    const double refraction_ratio = hit.front_face ? (1.0/m_ir)
                                                   : m_ir;

    // Check if ray is past the critical angle
    const bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    Vec3 direction;
    if (cannot_refract)
    {
        direction = Vec3::reflect(uv, hit.normal);
    }
    else
    {
        direction = Vec3::refract(uv, hit.normal, refraction_ratio);
    }

    // No light is absorbed
    o_attenuation = Color(1.0, 1.0, 1.0);
    o_scattered = Ray(hit.p, direction);

    return true;
}
