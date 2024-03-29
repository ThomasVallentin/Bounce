//
// Created by Thomas Vallentin on 20/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_SCENE_HPP
#define BOUNCE_SCENE_HPP

#include "Ray.h"
#include "Shape.hpp"
#include "Accelerator.hpp"
#include <vector>

class Light;

class Scene {
public:
    Scene() : accelerator(nullptr) {}
    explicit Scene(Accelerator* accelerator) : accelerator(accelerator) {}

    void addShape(Shape* h) { shapes.push_back(h); }
    void addLight(Light* h) { lights.push_back(h); }

    bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const;
    bool intersectAny(const Ray& ray, float tmin, float tmax);

    std::vector<Shape*> shapes;
    std::vector<Light*> lights;

    Accelerator* accelerator;
};

#endif //BOUNCE_SCENE_HPP
