#include "Shape.hpp"


bool ShapeList::intersect(const Ray& ray, float tmin, float tmax, HitData& data) const
{
    double closest_so_far = tmax;
    bool hit_anything = false;
    HitData temp_data;

    // std::cout << "tracing pixel with " << m_hitableList.size() << std::endl;
    for (Shape *shape : m_list) {
        // cout << m_hitableList[i] << endl;
        if (shape->intersect(ray, tmin, closest_so_far, temp_data)) {
            hit_anything = true;
            closest_so_far = temp_data.t;
            data = temp_data;
        }

    }
    return hit_anything;
}
