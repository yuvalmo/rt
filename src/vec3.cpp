#include "vec3.h"
#include "random.h"

#include <cmath>
#include <algorithm>

using std::all_of;
using std::begin;
using std::end;

/**
 * Getters
 */
double Vec3::x() const
{ return e[0]; }

double Vec3::y() const
{ return e[1]; }

double Vec3::z() const
{ return e[2]; }

double Vec3::length() const
{
    return std::sqrt(this->length_squared());
}

double Vec3::length_squared() const
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

bool Vec3::near_zero() const
{
    const auto s = 1e-8;

    // Check if close to zero in all dimensions
    return all_of(begin(e), end(e), [&s](const double x) {
        return fabs(x) < s;
    });
}

/**
 * Operators
 */
Vec3 Vec3::operator-() const
{
    return Vec3(-e[0], -e[1], -e[2]);
}

double Vec3::operator[](int i) const
{ return e[i]; }

double& Vec3::operator[](int i)
{ return e[i]; }

Vec3& Vec3::operator+=(const Vec3& other)
{
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
}

Vec3& Vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(const double t)
{
    return this->operator*=(1/t);
}

Vec3 Vec3::random()
{
    return {
        random_double(),
        random_double(),
        random_double()
    };
}

Vec3 Vec3::random(double min, double max)
{
    return {
        random_double(min, max),
        random_double(min, max),
        random_double(min, max)
    };
}

Vec3 Vec3::random_in_unit_sphere()
{
    while (true)
    {
        const auto p = Vec3::random(-1, 1);

        // Check if point is inside unit sphere
        if (p.length_squared() >= 1)
            continue;

        return p;
    }
}

Vec3 Vec3::random_unit_vector()
{
    // Normalize vector onto the surface of the sphere
    return unit_vector(random_in_unit_sphere());
}

Vec3 Vec3::random_in_hemisphere(const Vec3& normal)
{
    const auto v = random_in_unit_sphere();

    // If it points in the same overall direction of
    // the normal (in the same hemisphere)
    if (dot(v, normal) > 0.0)
    {
        return v;
    }

    // Should be flipped to point in the same
    // direction of the normal
    return -v;
}

Vec3 Vec3::reflect(const Vec3& v, const Vec3& n)
{
    const auto b =
        n            // Position along normal.
        * dot(v, n); // Scale according to angle and length of v.

    // Flip sign because the normal faces v, so the
    // dot product should be negative.
    return v - 2*b;
}

Vec3 Vec3::refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
    // Use dot product to replace cos theta
    const auto cos_theta = fmin(dot(-uv, n), 1.0);

    // Calculate vector parallel to normal and perpendicular
    // to it
    const auto r_out_perp = etai_over_etat * (uv + cos_theta*n);
    const auto r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;

    return r_out_perp + r_out_parallel;
}
