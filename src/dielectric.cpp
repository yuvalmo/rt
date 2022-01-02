#include "dielectric.h"
#include "random.h"

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

    Vec3 direction;
    if (ShouldReflect(cos_theta, sin_theta, refraction_ratio))
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

bool Dielectric::ShouldReflect(double cos_theta, double sin_theta, double refraction_ratio)
{
    // Check if ray is past the critical angle
    if (refraction_ratio * sin_theta > 1.0)
        return true;

    // Calculate ratio of reflected rays for this angle
    // based on schlick's approximation
    const auto reflectance = Reflectance(cos_theta, refraction_ratio);

    // Choose randomly whether to reflect or rafract. Since the reflectance
    // coefficient is higher for higher angles, we have more chance of 
    // reflecting in those angles.
    if (random_double() < reflectance)
        return true;

    return false;
}

double Dielectric::Reflectance(double cos_theta, double ref_idx)
{
    const double r0_sqrt = (1 - ref_idx) / (1 + ref_idx);
    const double r0 = r0_sqrt*r0_sqrt;

    return r0 + (1.0 - r0) * pow(1 - cos_theta, 5);
}
