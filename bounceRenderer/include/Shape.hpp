#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Shader.h"
#include "TransformObject.hpp"

class Shape : public TransformObject {

public:
    Shape(const Transform *objectToWorld, Shader* shader)
        : TransformObject(objectToWorld), shader(shader) {}
	virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;

    Shader* shader;
};


class ShapeList {

public:
    ShapeList() = default;

    std::vector<Shape*> list() { return m_list; };
    void addShape(Shape* h) { m_list.push_back(h); }

    bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const;

protected:
    std::vector<Shape*> m_list;
};
#endif