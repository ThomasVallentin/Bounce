//
// Created by Thomas Vallentin on 26/08/2020.
//

#include "BoundingBox.hpp"

bool BoundingBox::intersect(const Ray& ray) const {
    float xmin = (min.x - ray.origin.x) / ray.direction.x;
    float xmax = (max.x - ray.origin.x) / ray.direction.x;
    if (xmin > xmax)
        std::swap(xmin, xmax);

    float ymin = (min.y - ray.origin.y) / ray.direction.y;
    float ymax = (max.y - ray.origin.y) / ray.direction.y;
    if (ymin > ymax)
        std::swap(ymin, ymax);

    float zmin = (min.z - ray.origin.z) / ray.direction.z;
    float zmax = (max.z - ray.origin.z) / ray.direction.z;
    if (zmin > zmax)
        std::swap(zmin, zmax);

    float tLast = std::min(std::min(xmax, ymax), zmax);

    // intersection with the BB is done behind the ray
    if (tLast < 0)
        return false;

    return (tLast - std::max(std::max(xmin, ymin), zmin) >= 0);
}

bool BoundingBox::contains(const Point3& point) const {
    if (point.x < min.x)
        return false;
    if (point.y < min.y)
        return false;
    if (point.z < min.z)
        return false;
    if (point.x > max.x)
        return false;
    if (point.y > max.y)
        return false;
    if (point.z > max.z)
        return false;

    return true;
}
