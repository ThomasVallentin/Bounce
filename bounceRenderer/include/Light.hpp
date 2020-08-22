//
// Created by Thomas Vallentin on 19/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_LIGHT_HPP
#define BOUNCE_LIGHT_HPP

#include "Color.hpp"
#include "Ray.h"
#include "Scene.hpp"
#include "TransformObject.hpp"


class Light : public TransformObject {
public:
    Light() : TransformObject(),
              intensity(1.0f),
              color(1.0f, 1.0f, 1.0f) {}

    explicit Light(const Transform *worldToLight) : TransformObject(worldToLight),
                                                    intensity(1.0f),
                                                    color(1.0f, 1.0f, 1.0f) {}

    Light(const Transform *worldToLight, const Color &c, const float &i) : TransformObject(worldToLight),
                                                                           intensity(i),
                                                                           color(c) {}

    Color power() const { return color * intensity; }

    // Light interface. These methods are abstract and need to be reimplemented in concrete Lights.
    virtual Color getIllumination(const HitData &hit, Scene *scene) const = 0;
    virtual Point3 sample() const = 0;

    float intensity;
    Color color;
};


class PointLight : public Light {
public:
    PointLight() : Light() {}
    explicit PointLight(const Transform *worldToLight) : Light(worldToLight) {}
    PointLight(const Transform *worldToLight, const Color &c, const float &i) : Light(worldToLight, c, i) {}

    // Overrides
    Color getIllumination(const HitData &hitdata, Scene *scene) const override;

    Point3 sample() const override;
};

#endif //BOUNCE_LIGHT_HPP
