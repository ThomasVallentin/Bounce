//
// Created by Thomas Vallentin on 26/08/2020.
//

#ifndef BOUNCE_BOUNDINGBOX_H
#define BOUNCE_BOUNDINGBOX_H

#include "Ray.h"

class BoundingBox {
public:
    BoundingBox() = default;
    BoundingBox(const float &xmin, const float &ymin, const float &zmin,
                const float &xmax, const float& ymax, const float& zmax) :
            xmin(xmin), ymin(ymin), zmin(zmin), xmax(xmax), ymax(ymax), zmax(zmax) {}

    bool intersect(const Ray& ray) const;
    bool contains(const Point3& point) const;

    float xmin, ymin, zmin, xmax, ymax, zmax;
};


#endif //BOUNCE_BOUNDINGBOX_H
