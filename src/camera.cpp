#include "camera.h"

Camera::Camera(double aspect_ratio)
{
    // Camera
    const auto viewport_height = 2.0;
    const auto viewport_width = aspect_ratio * viewport_height;
    const auto focal_length = 1.0;

    m_origin = Point3(0, 0, 0);

    // Axis
    m_horizontal = Vec3(viewport_width, 0, 0); // X axis vector
    m_vertical = Vec3(0, viewport_height, 0);  // Y axis vector

    // Viewport
    m_lower_left_corner = m_origin
        - Vec3(0, 0, focal_length)  // Move onto viewport plane
        - m_horizontal / 2          // Move left
        - m_vertical / 2;           // Move down
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
