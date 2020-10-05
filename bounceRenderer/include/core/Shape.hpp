#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Ray.h"
#include "TransformObject.hpp"
#include "BoundingBox.hpp"

class Shape : virtual public TransformObject {

public:
    Shape() : TransformObject(), material(nullptr) {}
    Shape(const Transform *objectToWorld, Material* material)
        : TransformObject(objectToWorld), material(material) {}

    virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;
    virtual void buildBBox() = 0;
    virtual Point3 barycenter() = 0;

    Material* material;
    BoundingBox bbox;
};


#endif