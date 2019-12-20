#ifndef SPHEREH
#define SPHEREH

#include "Hitable.h"

class Sphere : public Hitable {

public:
	Sphere() { m_center = vector3(0.0, 0.0, 0.0); m_radius = 1.0; shader_ptr = new SurfaceShader(); };
	Sphere(const vector3& pos, float rad, string n) { m_center = pos; m_radius = rad; name = n; shader_ptr = new SurfaceShader(); }
	Sphere(float x, float y, float z, float rad, string n) { m_center = vector3(x, y, z); m_radius = rad; name = n; shader_ptr = new SurfaceShader(); }
	

	vector3 center() const { return m_center; }
	float radius() const { return m_radius; }
	virtual bool isHit(const Ray& ray, float tmin, float tmax, HitData& hit) const;

	//vector3 color() { return m_color;  }
	//void setColor(const vector3& col) { m_color = vector3(col); };
	//void setColor(float r, float g, float b) { m_color[0] = r; m_color[1] = g; m_color[2] = b; };

private:
	vector3 m_center;
	float m_radius;
	
	//vector3 m_color;
};

#endif