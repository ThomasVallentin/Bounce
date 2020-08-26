//
// Created by Thomas Vallentin on 26/08/2020.
//

#include "BoundingBox.hpp"

bool BoundingBox::intersect(const Ray& ray) const {
    float bxmin = (xmin - ray.origin.x) / ray.direction.x;
    float bxmax = (xmax - ray.origin.x) / ray.direction.x;
    if (bxmin > bxmax)
        std::swap(bxmin, bxmax);

    float bymin = (ymin - ray.origin.y) / ray.direction.y;
    float bymax = (ymax - ray.origin.y) / ray.direction.y;
    if (bymin > bymax)
        std::swap(bymin, bymax);

    float bzmin = (zmin - ray.origin.z) / ray.direction.z;
    float bzmax = (zmax - ray.origin.z) / ray.direction.z;
    if (bzmin > bzmax)
        std::swap(bzmin, bzmax);

    return (std::min(std::min(bxmax, bymax), bzmax) - std::max(std::max(bxmin, bymin), bzmin) > 0);
}

bool BoundingBox::contains(const Point3& point) const {
    if (point.x < xmin)
        return false;
    if (point.y < ymin)
        return false;
    if (point.z < zmin)
        return false;
    if (point.x > xmax)
        return false;
    if (point.y > ymax)
        return false;
    if (point.z > zmax)
        return false;

    return true;
}
