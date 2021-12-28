#pragma once


class Vec3
{
public:
    // Ctors
    Vec3() : e{0, 0, 0} {}
    Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // Getters
    double x() const;
    double y() const;
    double z() const;
    double length() const;
    double length_squared() const;

    // Operators
    Vec3 operator-() const;              // Reverse vector
    double operator[](int i) const;      // Get element
    double& operator[](int i);           // Get element ref
    Vec3& operator+=(const Vec3& other); // Add vector
    Vec3& operator*=(const double t);    // Multiply vector
    Vec3& operator/=(const double t);    // Divide vector

public:
    double e[3];
};

// Aliases
using Point3 = Vec3; // 3D point
using Color = Vec3;  // RGB color

#include "vec3_utils.h"
