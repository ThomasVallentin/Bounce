#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Ray.h"
#include "TransformObject.hpp"
#include "BoundingBox.hpp"

class Shape : public TransformObject {
public:
    Shape() : TransformObject(), material(nullptr) {}
    Shape(const Transform *objectToWorld, Material* material)
        : TransformObject(objectToWorld), material(material) {}

    virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;
    virtual void buildBBox() = 0;
    virtual Point3 barycenter() const = 0;

    virtual HitData sample(float &pdf) const { pdf = 0; return HitData(); }
    virtual float samplePdf(const HitData &hitdata) const { return 1 / area(); }

    virtual HitData sampleFromPoint(const HitData &from, float &pdf) const;

    virtual float area() const = 0 ;

    Material* material;
    BoundingBox bbox;
};


#endif