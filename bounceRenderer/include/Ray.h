#ifndef RAYH
#define RAYH

#include "vector3.h"
#include <iostream>

// just here to be able to create a pointer without creating a loop between ray and shader headers
class Shader;

class Ray {

public:
	Ray() = default;
	Ray(const vector3& o, const vector3& d) { origin = o; direction = d.unitVector(); }

	vector3 pointAtParameter(float t) const { return origin + t * direction; }

    vector3 origin;
    vector3 direction;
};

extern std::ostream& operator<<(std::ostream& os, const Ray& r);

struct HitData {
	double t;
	vector3 position;
	vector3 normal;
	Shader* shader_ptr;
};

#endif