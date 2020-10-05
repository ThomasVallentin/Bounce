//
// Created by Thomas Vallentin on 03/09/2020.
//

#include "samplers/RandomSampler.hpp"

void RandomSampler::initialize(RayTracer *tracer) {
    raytracer = tracer;

    width = tracer->camera().width();
    height = tracer->camera().height();
}

bool RandomSampler::sampleRay(unsigned int &u, unsigned int &v, Ray &ray) {
    std::unique_lock<std::mutex> lock(sampleLock);

    x++;

    if (x >= width) {
        // End of a row of pixel reset x, increment y
        x = 0;
        if (y >= height) {
            // End of the last row, reset y
            y = 0;
            if (raytracer->sampleBuffer[y * width + x] >= raytracer->maxSamples())
                return false;
        } else {
            y++;
        }
    }

    sampleCamera(ray);
    u = x;
    v = y;

    return true;
}

void RandomSampler::sampleCamera(Ray &ray) {
    // Sampling the camera using a very simple random sampling
    float urand = randomFlt();
    float vrand = randomFlt();
    float u = (float(x) + urand) / float(width);
    float v = (float(y) + vrand) / float(height);

    raytracer->camera().generateRay(u, v, ray);
}
