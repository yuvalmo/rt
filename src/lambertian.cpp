#include "lambertian.h"

Lambertian::Lambertian(const Color& albedo)
    : m_albedo(albedo)
{}

bool Lambertian::Scatter(const Ray& ray,
                         const HitRecord& hit,
                         Color& o_attenuation,
                         Ray& o_scattered) const
{
    // Choose point inside tangent sphere
    auto scatter_direction =
        hit.normal                     // Move to sphere center
        + Vec3::random_unit_vector();  // Move to random point on sphere

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
    {
        scatter_direction = hit.normal;
    }

    // Generate a bounce ray from hit point to that point
    o_scattered = Ray(hit.p, scatter_direction);
    o_attenuation = m_albedo;

    return true;
}
