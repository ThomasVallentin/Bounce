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
    virtual Color getIllumination(const HitData &hitdata, Scene *scene) const { return Color::Black(); }
    virtual Color getInfiniteIllumination(const Ray& ray) const { return Color::Black(); }

    float intensity;
    Color color;
};


class PointLight : public Light {
public:
    PointLight() : Light() {}
    explicit PointLight(const Transform *worldToLight) : Light(worldToLight) {}
    PointLight(const Transform *worldToLight, const Color &c, const float &i) : Light(worldToLight, c, i) {}

    Color getIllumination(const HitData &hitdata, Scene *scene) const override;
};


class DirectionalLight : virtual public Light {
public:
    DirectionalLight() : Light() {}
    explicit DirectionalLight(const Transform* transform) : Light(transform) {}
    DirectionalLight(const Transform* transform, const Color& c, const float& i) : Light(transform) {
        color = c;
        intensity = i;
    }

    Color getIllumination(const HitData &hitdata, Scene *scene) const override;
};

class EnvironmentLight : virtual public Light {
public:
    EnvironmentLight() : Light() {}
    EnvironmentLight(const Color& c, const float& i) : Light() { color = c; intensity = i; }
    Color getInfiniteIllumination(const Ray& ray) const override;
};


#endif //BOUNCE_LIGHT_HPP
