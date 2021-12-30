#include "metal.h"

Metal::Metal(const Color& albedo, double fuzz)
    : m_albedo(albedo),
      m_fuzz(std::min(fuzz, 1.0))
{}

bool Metal::Scatter(const Ray& ray,
                    const HitRecord& hit,
                    Color& o_attenuation,
                    Ray& o_scattered) const
{
    // Reflect ray across surface normal.
    // Offset by a random vector to make reflection fuzzy.
    const auto reflected = Vec3::reflect(ray.Direction(), hit.normal)
        + m_fuzz * Vec3::random_in_unit_sphere();

    o_scattered = Ray(hit.p, reflected);
    o_attenuation = m_albedo;

    // Catch rays that are reflected below the surface
    // by absorbing them.
    return (dot(o_scattered.Direction(), hit.normal) > 0);
}
