//
// Created by Thomas Vallentin on 01/09/2020.
//

#ifndef BOUNCE_HIERARCHICALADAPTIVE_HPP
#define BOUNCE_HIERARCHICALADAPTIVE_HPP


#include "core/RayTracer.hpp"
#include "core/Sampler.hpp"


struct Block {
    Block() = default;
    Block(const unsigned int &xMin, const unsigned int &yMin, const unsigned int &xMax, const unsigned int &yMax) :
            xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax), width(xMax - xMin), height(yMax - yMin) {}
    unsigned int xMin, yMin, xMax, yMax, width, height;
};


class HierarchicalAdaptive : public Sampler {
public:
    explicit HierarchicalAdaptive(const float& threshold) : Sampler(), threshold(threshold) {}

    void initialize(RayTracer* tracer) override;
    bool sampleRay(unsigned int &u, unsigned int &v, Ray &ray) override;
    void sampleCamera(Ray &ray) override;
    void update(const unsigned int &u, const unsigned int &v, const Color& color) override;

private:
    float computeError(Block* block);

    float threshold;
    float splitThreshold = 0.0f;

    unsigned int minBlockSize = 32;
    std::vector<float> buffer;
    std::queue<Block*> blocks;
    unsigned int width = 0, height = 0;
    int x = -1, y = 0;
    Block* currentBlock;
    std::mutex sampleLock;

    RayTracer * raytracer;
};


#endif //BOUNCE_HIERARCHICALADAPTIVE_HPP
