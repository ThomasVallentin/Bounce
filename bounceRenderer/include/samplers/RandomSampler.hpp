//
// Created by Thomas Vallentin on 03/09/2020.
//

#ifndef BOUNCE_RANDOMSAMPLER_HPP
#define BOUNCE_RANDOMSAMPLER_HPP


#include "core/Sampler.hpp"
#include "core/RayTracer.hpp"


class RandomSampler : public Sampler{
public:
    RandomSampler() : Sampler() {}

    void initialize(RayTracer* tracer) override;
    bool sampleRay(unsigned int &u, unsigned int &v, Ray &ray) override;
    void sampleCamera(Ray &ray) override;
    void update(const unsigned int &u, const unsigned int &v, const Color& color) override {};

private:
    RayTracer *raytracer = nullptr;
    int x = -1, y = 0;
    unsigned int width=0, height=0;
    std::mutex sampleLock;
};


#endif //BOUNCE_RANDOMSAMPLER_HPP
