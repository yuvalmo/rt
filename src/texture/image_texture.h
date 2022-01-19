#pragma once

#include "texture.h"

#include <image.h>
#include <memory>


class ImageTexture : public Texture
{
public:
    ImageTexture(std::shared_ptr<Image> image);

public: 
    Color Value(double u, double v, const Point3& p) const override;

private:
    std::shared_ptr<Image> m_image;
};

