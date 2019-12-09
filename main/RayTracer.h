#ifndef RAYTRACERH
#define RAYTRACERH
#include <vector>

#include "HitableComposite.h"
#include "Sphere.h"
#include "Camera.h"
using namespace std;

class RayTracer {

public:
	RayTracer() { 
		m_width = 400; m_height = 200; m_near_clip = 0.001; m_far_clip = 100000; m_samples = 1; 
	}
	RayTracer(float x, float y, int near_clip=0.001, int far_clip =10000, int sample=100) {
		m_width = x; m_height = y;  m_near_clip = near_clip; m_far_clip = far_clip; m_samples = sample; 
	}

	string outpath() { return m_outpath; }
	void setOutpath(const string str) { m_outpath = str; }

	int width() { return m_width; }
	void setWidth(int x) { m_width = x; }

	int height() { return m_height; }
	void setHeight(int y) { m_height = y; }

	int nearClip() { return m_near_clip; };
	void setNearClip(int min) { m_near_clip = min; };

	int farClip() { return m_far_clip; };
	void setFarClip(int max) { m_far_clip = max; };

	int samples() { return m_samples; };
	void setSamples(int samples) { m_samples = samples; };

	void addHitable( Hitable* h) { m_world.addHitable(h); }
	HitableComposite ls() { return m_world; }
	bool trace(const Camera& camera);

private:
	float m_width;
	float m_height;

	int m_near_clip;
	int m_far_clip;

	int m_samples;

	string m_outpath;

	HitableComposite m_world;
};

#endif
