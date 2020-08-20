#ifndef RAYTRACERH
#define RAYTRACERH

#include "Scene.hpp"
#include "FileAdapters.h"
#include "Shape.hpp"
#include "Sphere.h"
#include "Camera.hpp"
#include "mathUtils.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

class RayTracer {

public:
	RayTracer() : m_near_clip(0.001), m_far_clip(100000), m_samples(100), m_max_depth(50), m_gamma(2.2) {}
	RayTracer(float near_clip = 0.001, float far_clip = 10000, int sample = 100) :
	    m_near_clip(near_clip), m_far_clip(far_clip), m_samples(sample), m_max_depth(50), m_gamma(2.2f) {}

    std::string outpath() { return m_outpath; }
	void setOutpath(const std::string& str) { m_outpath = std::string(str); }

	int samples() { return m_samples; };
	void setSamples(int samples) { m_samples = samples; };

    float gamma() { return m_gamma; };
	void setGamma(float gamma) { m_gamma = gamma; };

    Camera &camera() { return m_camera; };
	void setCamera(Camera &cam) { m_camera = cam; };

	bool initialize();
    void sampleCamera(const unsigned int &x, const unsigned int &y, Ray& ray);
    bool trace(Scene* sc);
	Color computeIllumination(const Ray& ray, int depth=0) const;
	void mergeColorToPixel(const unsigned int &x, const unsigned int &y, unsigned int &currentSample, Color& color);

	Shader* m_default_shader = new Lambert();

    std::vector<float>& pixels() { return m_pixels; };

private:
    float m_near_clip;
    float m_far_clip;

	int m_samples;
	int m_max_depth;

	float m_gamma;

	Camera m_camera;

    std::string m_outpath;
    std::vector<float> m_pixels;

    Scene* scene;
};

#endif
