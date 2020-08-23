#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Shader.hpp"
#include "TransformObject.hpp"

class Shape : public TransformObject {

public:
    Shape(const Transform *objectToWorld, Shader* shader)
        : TransformObject(objectToWorld), shader(shader) {}
	virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;

    Shader* shader;
};


#endif