/**
 * A list of hittable objects.
 */
#pragma once

#include <hittable.h>

#include <memory>
#include <vector>

/**
 * A composite class of hittables.
 */
class HittableList : public Hittable
{
public:
    using SharedHittable = std::shared_ptr<Hittable>;

public:
    HittableList() = default;
    HittableList(SharedHittable object);

    void clear();
    void add(SharedHittable object);

    bool Hit(const Ray& ray,
             double t_min,
             double t_max,
             HitRecord& o_rec) const override;

private:
    std::vector<std::shared_ptr<Hittable>> m_objects;
};
