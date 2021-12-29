#include "vec3.h"
#include "random.h"

#include <cmath>

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

/**
 * Operators
 */
Vec3 Vec3::operator-() const
{
    return Vec3(-e[0], -e[1], -e[2]);
}

// Get element
double Vec3::operator[](int i) const
{ return e[i]; }

// Get element ref
double& Vec3::operator[](int i)
{ return e[i]; }

// Add vector
Vec3& Vec3::operator+=(const Vec3& other)
{
    e[0] += other.e[0];
    e[1] += other.e[1];
    e[2] += other.e[2];
    return *this;
}

// Multiply vector
Vec3& Vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

// Divide vector
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
