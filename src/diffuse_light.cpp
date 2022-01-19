#include "diffuse_light.h"

#include <texture/solid_color.h>


DiffuseLight::DiffuseLight(std::shared_ptr<Texture> emit)
    : m_emit(emit)
{}

DiffuseLight::DiffuseLight(Color color)
    : m_emit(std::make_shared<SolidColor>(color))
{}

bool DiffuseLight::Scatter(const Ray&,
                           const HitRecord&,
                           Color&,
                           Ray&) const
{
    // A light material scatters no rays.
    return false;
}

Color DiffuseLight::Emitted(double u,
                            double v,
                            const Point3& p) const
{
    return m_emit->Value(u, v, p);
}

