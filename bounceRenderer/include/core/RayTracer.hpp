#ifndef RAYTRACERH
#define RAYTRACERH

#include "Scene.hpp"
#include "BSDF.hpp"
#include "Light.hpp"
#include "FileAdapters.hpp"
#include "Sampler.hpp"
#include "Shape.hpp"
#include "Camera.hpp"
#include "threading.hpp"
#include "mathUtils.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

struct Tile {
    Tile(const unsigned int& x, const unsigned int& y, const unsigned int& width, const unsigned int& height) :
            x(x), y(y), width(width), height(height), buffer(width * height) {}

    unsigned int x, y, width, height;
    std::vector<Color> buffer;
};

class RayTracer {

public:
	RayTracer() :
            nearClip(0.001), farClip(100000), samplesMin(8), samplesMax(50), m_max_depth(1), m_gamma(2.2), adapter(nullptr) {}
	RayTracer(float near_clip, float far_clip, const unsigned int& minsample, const unsigned int& maxsample) :
            nearClip(near_clip), farClip(far_clip), samplesMin(minsample), samplesMax(maxsample), m_max_depth(1), m_gamma(2.2f), adapter(nullptr) {}

    std::string outpath() const { return m_outpath; }
	void setOutpath(const std::string& str) { m_outpath = std::string(str); }
	void setAdapter(FileAdapter* adapt) { adapter = adapt; }

	unsigned  int minSamples() const { return samplesMin; };
	void setMinSamples(const unsigned int& samples) { samplesMin = samples; };

	unsigned int maxSamples() const { return samplesMax; };
	void setMaxSamples(const unsigned int& samples) { samplesMax = samples; };
	void setSamples(const unsigned int& min, const unsigned int& max) { samplesMin = min; samplesMax = max; };

    float gamma() const { return m_gamma; };
	void setGamma(float gamma) { m_gamma = gamma; };

    unsigned int threadCount() const { return threadPool.threadCount; };
	void setThreadCount(const unsigned int& thrds) { threadPool.threadCount = thrds; };

    Camera &camera() { return m_camera; };
	void setCamera(Camera &cam) { m_camera = cam; };

//    Sampler* sampler() { return m_sampler; };
	void setSampler(Sampler* smplr) { m_sampler = smplr; };

    void initialize(Scene* sc);
    bool isInitialized() { return initialized; }
    void render(Scene* sc);
    void trace();
    bool threadedTrace();
    void sampleCamera(const unsigned int &x, const unsigned int &y, Ray& ray);
    Color computeIllumination(const Ray& ray, int depth=0) const;
    Color sampleLight(const Light *light, HitData &hitdata) const;
    Color sampleAllLights(HitData &hitdata) const;
	void mergeColorToPixel(const unsigned int &x, const unsigned int &y, Color& color);
    bool writeImage() const;

//	Shader* m_default_shader = new Lambert(0.5f, 0.5f, 0.5f);

    std::vector<float>& pixels() { return pixelBuffer; };
    std::vector<float> pixelBuffer;

    std::vector<unsigned int> sampleBuffer;

private:
    float nearClip;
    float farClip;

	unsigned int samplesMin;
	unsigned int samplesMax;
	int m_max_depth;

	float m_gamma;

	Camera m_camera;

    std::string m_outpath;

    Scene* scene = nullptr;
    FileAdapter* adapter;

    float adaptiveThreshold;
    Sampler* m_sampler;

    ThreadPool threadPool;
    std::mutex writingPixelsMutex;
    float tileCount = 0;
    float progress = 0;
    bool initialized = false;
};

#endif
