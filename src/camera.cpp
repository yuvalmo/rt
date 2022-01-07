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
               double aspect_ratio,
               double aperture,
               double focus_dist)
{
    // Calculate field of vision
    const auto theta = to_radians(vfov);
    const auto h = tan(theta / 2);

    // Camera
    const auto viewport_height = 2.0 * h;
    const auto viewport_width = aspect_ratio * viewport_height;

    m_origin = lookfrom;

    // Axes
    m_cz = unit_vector(lookat - lookfrom); // z axis (camera forward)
    m_cx = unit_vector(cross(m_cz, vup));  // x axis (camera right)
    m_cy = -cross(m_cz, m_cx);             // y axis (camera up)

    // Scale viewport correctly.
    // Multiplying by focus_dist scales them to be the right
    // distance from the origin, while maintaining the same
    // relative size (the direction of the rays from the origin
    // to the corners of the viewport stays the same.
    m_horizontal = m_cx * focus_dist * viewport_width;
    m_vertical   = m_cy * focus_dist * viewport_height;

    // Viewport
    m_lower_left_corner = m_origin
        + m_cz * focus_dist  // Move onto viewport plane
        - m_horizontal / 2   // Move left
        - m_vertical / 2;    // Move down

    // Lens radius
    m_lens_radius = aperture / 2;
}

Ray Camera::GetRay(double u, double v) const
{
    // Generate random point in disk and rotate
    // it to camera's axes.
    const auto rd = Vec3::random_in_unit_disk() * m_lens_radius;
    const auto offset = m_cx * rd.x() +
                        m_cy * rd.y();

    // Calculate random ray origin
    const auto origin = m_origin + offset;

    // Calculate point on viewport
    const auto p = m_lower_left_corner
        + u * m_horizontal // Translate across x axis
        + v * m_vertical   // Translate across y axis
        - origin;          // Follow camera

    // Shoot ray at point
    return Ray(origin, p);
}
