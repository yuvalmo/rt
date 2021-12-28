/**
 * Vec3 utility functions.
 */
#pragma once

#include "vec3.h"
#include <iostream>

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
    return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t * v;
}

inline Vec3 operator/(const Vec3& v, double t)
{
    return (1/t) * v;
}

/**
 * Dot product of two vectors.
 *
 * Can be used as an indication for the degree in which
 * two vectors point in the same direction.
 *
 * @return > 0 when pointing in roughly the same direction.
 *         = 0 when perpendicular.
 *         < 0 when pointing in roughly the opposite direction.
 */
inline double dot(const Vec3& u, const Vec3& v)
{
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

/**
 * Cross product of two vectors.
 *
 * Returns a vector perpendicular to the plane created by
 * those two vectors. The vectors magnitude the same as 
 * the area of a parallogram created by the two vectors.
 */
inline Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

/**
 * Scales the vector so its angle stays the same
 * but, its length is equal to one.
 */
inline Vec3 unit_vector(const Vec3& v)
{
    return v / v.length();
}
