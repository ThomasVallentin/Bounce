#ifndef SPHEREH
#define SPHEREH

#include "Ray.h"

class Sphere
{
public:
	Sphere() { m_center = vector3(0.0, 0.0, 0.0); m_radius = 1.0; };
	Sphere(const vector3& pos, float rad) { m_center = pos; m_radius = rad; }
	Sphere(float x, float y, float z, float rad) { m_center = vector3(x,y,z); m_radius = rad; }

	vector3 center() const { return m_center; }
	float radius() const { return m_radius; }
	float isHit(const Ray& ray) const;

	vector3 color() { return m_color;  }
	void setColor(const vector3& col) { m_color = vector3(col); };
	void setColor(float r, float g, float b) { m_color[0] = r; m_color[1] = g; m_color[2] = b; };

private:
	vector3 m_center;
	float m_radius;
	vector3 m_color;
};

#endif