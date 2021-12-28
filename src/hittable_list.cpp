#include "hittable_list.h"


HittableList::HittableList(SharedHittable object)
    : m_objects()
{
    this->add(object);
}

void HittableList::clear()
{
    m_objects.clear();
}

void HittableList::add(SharedHittable object)
{
    m_objects.push_back(object);
}

bool HittableList::Hit(const Ray& ray,
                       double t_min,
                       double t_max,
                       HitRecord& o_rec) const
{
    bool hit_anything = false;
    auto closest_so_far = t_max;

    // Find closest hit
    for (const auto& hittable : m_objects)
    {
        HitRecord hit;
        if (hittable->Hit(ray, t_min, closest_so_far, hit))
        {
            hit_anything = true;
            o_rec = hit;

            // Set new t_max so we only record a closer hit
            closest_so_far = hit.t;
        }
    }

    return hit_anything;
}
