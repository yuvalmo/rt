#include "lambertian.h"
#include <texture/solid_color.h>

Lambertian::Lambertian(const Color& albedo)
    : m_albedo(std::make_shared<SolidColor>(albedo))
{}

Lambertian::Lambertian(std::shared_ptr<Texture> texture)
    : m_albedo(texture)
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
    o_attenuation = m_albedo->Value(hit.u, hit.v, hit.p);

    return true;
}
