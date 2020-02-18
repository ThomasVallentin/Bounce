#ifndef RAYTRACERH
#define RAYTRACERH
#include <vector>
#include <cstdint>

#include "HitableComposite.h"
#include "Sphere.h"
#include "Camera.h"
#include "mathUtils.h"

using namespace std;

class RayTracer {

public:
	RayTracer() { 
		m_width = 400; m_height = 200; m_near_clip = 0.001; m_far_clip = 100000; m_samples = 100; m_max_depth = 50; m_gamma = 2.2; }

	RayTracer(float x, float y, int near_clip = 0.001, int far_clip = 10000, int sample = 100) {
		m_width = x; m_height = y;  m_near_clip = near_clip; m_far_clip = far_clip; m_samples = sample; m_max_depth = 50; m_gamma = 2.2; }

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
	
	float gamma() { return m_gamma; };
	void setGamma(float gamma) { m_gamma = gamma; };

	void addHitable( Hitable* h) { m_world.addHitable(h); }
	HitableComposite ls() { return m_world; }

	bool initialize();
	bool trace(const Camera& camera);
	Ray generateRay(const Camera& camera, float u, float v) const;
	vector3 computeRay(const Ray& ray, int depth) const;

	Shader* m_default_shader = new Lambert();

	vector<float> m_result;

private:
	int m_width;
	int m_height;

	int m_near_clip;
	int m_far_clip;

	int m_samples;
	int m_max_depth;

	float m_gamma;

	string m_outpath;

	HitableComposite m_world;
};

extern vector3 unitToColor(const vector3& vec);
extern vector3 applyGamma(const vector3& color, float gamma);

#endif
