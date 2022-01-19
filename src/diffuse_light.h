#pragma once

#include <material.h>
#include <texture/texture.h>

#include <memory>


/**
 * A material that emits light and scatters
 * none of it.
 */
class DiffuseLight : public Material
{
public:
    DiffuseLight(std::shared_ptr<Texture> texture);
    DiffuseLight(Color color);

    bool Scatter(const Ray& ray,
                 const HitRecord& hit,
                 Color& o_attenuation,
                 Ray& o_scattered) const override;

    Color Emitted(double u,
                  double v,
                  const Point3& p) const override;

private:
    std::shared_ptr<Texture> m_emit;
};

