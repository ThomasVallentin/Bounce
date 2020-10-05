//
// Created by Thomas Vallentin on 26/08/2020.
//

#ifndef BOUNCE_BOUNDINGBOX_H
#define BOUNCE_BOUNDINGBOX_H

#include "Ray.h"

class BoundingBox {
public:
    BoundingBox() = default;
    BoundingBox(const BoundingBox& bb) :
            min(bb.min), max(bb.max) {}
    BoundingBox(const Vector3& min, const Vector3& max) :
            min(min), max(max) {}
    BoundingBox(const float &xmin, const float &ymin, const float &zmin,
                const float &xmax, const float& ymax, const float& zmax) :
            min(xmin, ymin, zmin), max(xmax, ymax, zmax) {}

    bool intersect(const Ray& ray) const;
    bool contains(const Point3& point) const;

    Point3 min, max;
};


#endif //BOUNCE_BOUNDINGBOX_H
