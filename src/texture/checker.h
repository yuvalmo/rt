#pragma once

#include "texture.h"
#include <memory>

/**
 * A checkered texture that alternates between
 * two textures. If colors are given, alternates
 * between two solid textures.
 */
class CheckerTexture : public Texture
{
public:
    CheckerTexture(Color odd, Color even);
    CheckerTexture(std::shared_ptr<Texture> even,
                   std::shared_ptr<Texture> odd);

public:
    Color Value(double u, double v, const Point3& p) const override;

private:
    std::shared_ptr<Texture> m_even;
    std::shared_ptr<Texture> m_odd;
};

