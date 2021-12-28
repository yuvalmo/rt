#include "vec3.h"
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
