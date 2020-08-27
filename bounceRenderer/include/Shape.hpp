#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Ray.h"
#include "TransformObject.hpp"
#include "BoundingBox.hpp"

class Shape : virtual public TransformObject {

public:
    Shape() : TransformObject(), shader(nullptr) {}
    Shape(const Transform *objectToWorld, Shader* shader)
        : TransformObject(objectToWorld), shader(shader) {}

    virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;
    virtual void buildBBox() = 0;
    virtual Point3 barycenter() = 0;

    Shader* shader;
    BoundingBox bbox;
};


#endif