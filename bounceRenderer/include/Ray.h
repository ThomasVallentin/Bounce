#ifndef RAYH
#define RAYH

#include "Vector3.hpp"
#include "Point3.hpp"
#include <iostream>

// just here to be able to create a pointer without creating a loop between ray and shader headers
class Shader;

class Ray {

public:
	Ray() = default;
	Ray(const Vector3& o, const Vector3& d) { origin = o; direction = d.normalized(); }

	Point3 pointAtParameter(float t) const { return origin + direction * t; }

    Point3 origin;
    Vector3 direction;
};

extern std::ostream& operator<<(std::ostream& os, const Ray& r);

struct HitData {
	double t;
	Vector3 position;
	Vector3 normal;
	Shader* shader_ptr;
};

#endif