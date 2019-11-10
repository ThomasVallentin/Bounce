#ifndef RAYTRACERH
#define RAYTRACERH
#include <vector>

#include "Sphere.h"

using namespace std;

class RayTracer
{
public:
	RayTracer();
	RayTracer(float x, float y) { m_width = x; m_height = y; }

	string outpath() { return m_outpath; }
	void setOutpath(const string str) { m_outpath = str; }

	int width() { return m_width; }
	void setWidth(int x) { m_width = x; }

	int height() { return m_height; }
	void setHeight(int y) { m_height = y; }

	void addSphere(const Sphere& sph) { m_objectList[m_objectList.size()] = sph; }
	bool trace();

private:
	float m_width;
	float m_height;

	string m_outpath;

	vector<Sphere> m_objectList;

};

#endif
