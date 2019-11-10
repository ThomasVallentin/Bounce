#ifndef SPHEREH
#define SPHEREH

#include "Ray.h"

class Sphere
{
public:
	Sphere() { m_position = vector3(0.0, 0.0, 0.0); m_radius = 1.0; };
	Sphere(const vector3& pos, float rad) { m_position = pos; m_radius = rad; }
	Sphere(float x, float y, float z, float rad) { m_position = vector3(x,y,z); m_radius = rad; }

	vector3 position() const { return m_position; }
	float radius() const { return m_radius; }
	bool isHit(const Ray& r) const;

	vector3 m_position;
	float m_radius;
};

#endif