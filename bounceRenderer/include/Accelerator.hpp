//
// Created by Thomas Vallentin on 26/08/2020.
//

#ifndef BOUNCE_ACCELERATOR_HPP
#define BOUNCE_ACCELERATOR_HPP

#include "BoundingBox.hpp"

class Scene;

class Accelerator {
public:
    Accelerator() : scene(nullptr) {}
    explicit Accelerator(Scene* scene) : scene(scene) {}

    virtual bool build() = 0;
    virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;
    virtual bool intersectAny(const Ray& ray, float tmin, float tmax, HitData& tempdata) const = 0;

    Scene* scene;
};

#endif //BOUNCE_ACCELERATOR_HPP
