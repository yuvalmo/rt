#include "sphere.h"

#include <math_utils.h>

Sphere::Sphere(Point3 center, double radius, MaterialPtr material)
    : m_center(center), m_radius(radius), m_material(material)
{}

bool Sphere::Hit(const Ray& ray,
                 double t_min,
                 double t_max,
                 HitRecord& o_rec) const
{
    // Vector from ray's origin to sphere's center
    const auto oc = ray.Origin() - m_center;

    // Solve quadratic equation
    const auto a = ray.Direction().length_squared();
    const auto half_b = dot(oc, ray.Direction());
    const auto c = oc.length_squared() - m_radius*m_radius;
    const auto discriminant = half_b*half_b - a*c;

    // No hit
    if (discriminant < 0) return false;

    const auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    o_rec.t = root;
    o_rec.p = ray.At(root);
    o_rec.material = m_material;

    // Make normal face ray
    const auto outward_normal = (o_rec.p - m_center) / m_radius;
    o_rec.SetFaceNormal(ray, outward_normal);

    // Calculate uv coordinates
    get_uv(outward_normal, o_rec.u, o_rec.v);

    return true;
}

void Sphere::get_uv(const Point3& p,
                    double& o_u,
                    double& o_v)
{
    // Calculate angles from origin to
    const auto phi = atan2(-p.z(), p.x()) + PI;
    const auto theta = acos(-p.y());

    // Normalize into [0, 1] range

    // u goes counter-clockwise from side to side, which means
    // it should be divided by the whole circumference.
    o_u = phi / (2*PI);

    // u goes from facing down to facing up, and covers only
    // half the circumference.
    o_v = theta / PI;
}
