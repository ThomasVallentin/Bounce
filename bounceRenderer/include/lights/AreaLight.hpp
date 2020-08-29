//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_AREALIGHT_HPP
#define BOUNCE_AREALIGHT_HPP

#include <TriangleMesh.hpp>
#include "Light.hpp"
#include "Shader.hpp"

class AreaLight : public Shape, public Light {
public:
    AreaLight() :
            Shape(),
            Light(),
            TransformObject(),
            samples(2)
            { shader = new LightShader(this);
                }
        explicit AreaLight(const Transform* transform) :
            Shape(transform, new LightShader(this)),
            Light(transform),
            TransformObject(transform),
            samples(2) {}
    AreaLight(const Transform* transform, const Color& c, const float& i) :
            Shape(transform, new LightShader(this)),
            Light(transform, c, i),
            TransformObject(transform),
            samples(2) {}

    unsigned int samples;
};


class DiscLight : public AreaLight {
public:
    DiscLight() :
            AreaLight(), radius(1.0f) {}
    explicit DiscLight(const Transform* transform) :
            AreaLight(transform), TransformObject(transform), radius(1.0f) {}
    DiscLight(const Transform* transform, const float& radius, const Color& c, const float& i) :
            AreaLight(transform, c, i), TransformObject(transform), radius(radius) {}

    Color getIllumination(const HitData &hitdata, Scene *scene) const override;
    bool intersect(const Ray &ray, float tmin, float tmax, HitData &data) const override;
    virtual void buildBBox() override;
    virtual Point3 barycenter() override;

    float radius{};
};

#endif //BOUNCE_AREALIGHT_HPP
