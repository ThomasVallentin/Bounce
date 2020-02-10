#ifndef RAYH
#define RAYH

#include "vector3.h"
#include <iostream>

// just here to be able to create a pointer without creating a loop between ray and shader headers
class Shader;

class Ray {

public:
	Ray() {}
	Ray(const vector3& o, const vector3& d) { m_origin = o; m_direction = d.unitVector(); }

	vector3 origin() const { return m_origin; }
	vector3 direction() const { return m_direction; }
	vector3 pointAtParameter(float t) const { return m_origin + t * m_direction; }

private:
	vector3 m_origin;
	vector3 m_direction;
};

extern ostream& operator<<(ostream& os, const Ray& r);

struct HitData {
	double t;
	vector3 position;
	vector3 normal;
	Shader* shader_ptr;
};

#endif