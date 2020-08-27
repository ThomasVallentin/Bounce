#ifndef SPHEREH
#define SPHEREH

#include "Shape.hpp"

class Sphere : public Shape {

public:
	Sphere(const Transform *objectToWorld, float rad, Shader* shader)
            : Shape(objectToWorld, shader), m_radius(rad), m_center(objectToWorld->matrix.m[3][0],
                                                                    objectToWorld->matrix.m[3][1],
                                                                    objectToWorld->matrix.m[3][2]) {}

    Point3 center() const { return m_center; }
    float radius() const { return m_radius; }
	bool intersect(const Ray& ray, float tmin, float tmax, HitData& hit) const override;
    void buildBBox() override;
    Point3 barycenter() override;

private:
	Point3 m_center;
	float m_radius;
	
};

#endif