#include "metal.h"

Metal::Metal(const Color& albedo)
    : m_albedo(albedo)
{}

bool Metal::Scatter(const Ray& ray,
                    const HitRecord& hit,
                    Color& o_attenuation,
                    Ray& o_scattered) const
{
    // Reflect ray across surface normal
    const auto reflected = Vec3::reflect(ray.Direction(), hit.normal);

    o_scattered = Ray(hit.p, reflected);
    o_attenuation = m_albedo;

    // Catch rays that are perpendicular to the normal,
    // which are only tangent to the surface.
    return (dot(o_scattered.Direction(), hit.normal) > 0);
}
