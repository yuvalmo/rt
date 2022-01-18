#include "checker.h"
#include "solid_color.h"

#include <math_utils.h>

CheckerTexture::CheckerTexture(Color even, Color odd)
    : CheckerTexture(std::make_shared<SolidColor>(even),
                     std::make_shared<SolidColor>(odd))
{}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even,
                               std::shared_ptr<Texture> odd)
    : m_even(even),
      m_odd(odd)
{}

Color CheckerTexture::Value(double u, double v, const Point3& p) const
{
    const auto sines = sin(10*p.x()) *
                       sin(10*p.y()) *
                       sin(10*p.z());

    return (sines < 0)
        ? m_odd->Value(u, v, p)
        : m_even->Value(u, v, p);
}
