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
    // The number of strips going from top to bottom (f is for frequency).
    const auto f = 40;

    // Multiply u by 2 because it travels twice the distance.
    // This makes the tiles square, instead of streching them.
    const auto even_u = int(u*2*f) % 2 == 0;
    const auto even_v = int(v*f) % 2 == 0;

    return (even_u == even_v)
        ? m_odd->Value(u, v, p)
        : m_even->Value(u, v, p);
}
