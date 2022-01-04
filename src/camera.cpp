#include "camera.h"
#include "math_utils.h"

double to_radians(double degrees)
{
    return degrees * PI / 180.0;
}

Camera::Camera(Point3 lookfrom,
               Point3 lookat,
               Vec3 vup,
               double vfov,
               double aspect_ratio)
{
    // Calculate field of vision
    const auto theta = to_radians(vfov);
    const auto h = tan(theta / 2);

    // Camera
    const auto viewport_height = 2.0 * h;
    const auto viewport_width = aspect_ratio * viewport_height;
    const auto focal_length = 1.0;

    m_origin = lookfrom;

    // Axis
    const auto depth = unit_vector(lookat - lookfrom); // z axis (camera forward)
    const auto hor   = unit_vector(cross(depth, vup)); // x axis (camera right)
    const auto ver   = -cross(depth, hor);  // y axis (camera up)

    // Scale them correctly
    m_horizontal = unit_vector(hor) * viewport_width;
    m_vertical   = unit_vector(ver) * viewport_height;

    // Viewport
    m_lower_left_corner = m_origin
        + unit_vector(depth) * focal_length  // Move onto viewport plane
        - m_horizontal / 2                   // Move left
        - m_vertical / 2;                    // Move down
}

Ray Camera::GetRay(double u, double v) const
{
    // Calculate point on viewport
    const auto p = m_lower_left_corner
        + u * m_horizontal // Translate across x axis
        + v * m_vertical   // Translate across y axis
        - m_origin;        // Follow camera

    // Shoot ray at point
    return Ray(m_origin, p);
}
