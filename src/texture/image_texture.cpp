#include "image_texture.h"

ImageTexture::ImageTexture(std::shared_ptr<Image> image)
    : m_image(image)
{}

Color ImageTexture::Value(double u, double v, const Point3& p) const
{
    return m_image->GetColor(u, v);
}
