#include "ray.h"

Ray::Ray(const Point3& origin, const Vec3& direction)
    : m_origin(origin),
      m_direction(direction)
{}

Point3 Ray::At(double t) const
{
    return m_origin + (t * m_direction);
}
