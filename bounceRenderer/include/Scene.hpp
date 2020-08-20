//
// Created by Thomas Vallentin on 20/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_SCENE_HPP
#define BOUNCE_SCENE_HPP

#include "Shape.hpp"
#include "Light.hpp"

class Scene {
public:
    Scene() = default;

    std::vector<Shape*> shapes() { return shapeList; };
    std::vector<Light*> lights() { return lightList; };
    void addShape(Shape* h) { shapeList.push_back(h); }
    void addLight(Light* h) { lightList.push_back(h); }

    bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const;

protected:
    std::vector<Shape*> shapeList;
    std::vector<Light*> lightList;
};

#endif //BOUNCE_SCENE_HPP
