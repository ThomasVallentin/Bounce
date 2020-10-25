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
              color(1.0f, 1.0f, 1.0f),
              samples(1),
              decay(2.0f) {}

    Light(const Transform *worldToLight) :
            TransformObject(worldToLight),
            intensity(1.0f),
            color(1.0f, 1.0f, 1.0f),
            samples(1),
            decay(2.0f) {}
    Light(const Transform *worldToLight, const Color &c, const float &i) :
            TransformObject(worldToLight),
            intensity(i),
            color(c),
            samples(1),
            decay(2.0f) {}
    Light(const Transform *worldToLight, const Color &c, const float &i, unsigned int samples) :
            TransformObject(worldToLight),
            intensity(i),
            color(c),
            samples(samples),
            decay(2.0f) {}

    Color power() const { return color * intensity; }
    virtual Color sample(const HitData &hitdata, Vector3 &wi, Point3 &sampleP, float &pdf) const { pdf=0; return Color::Black(); }
    virtual float computePdf(const HitData &hitdata, const Vector3& w) const { return 0; };
    virtual Color getInfiniteIllumination(const Ray &ray) const { return Color::Black(); }

    float intensity;
    Color color;
    unsigned int samples;
    float decay;
};


class AreaLight : public Light {
public:
    AreaLight() : Light() {}

    explicit AreaLight(const Transform *transform, const int &samples, Shape *shape);

    AreaLight(const Transform *transform, const Color &c, const float &i, const int &samples, Shape *shape);

    Color sample(const HitData &hitdata, Vector3 &wi, Point3 &sampleP, float &pdf) const override;
    virtual Color lightEmitted(const HitData &hitdata, const Vector3 &w) const = 0;
    float computePdf(const HitData &hitdata, const Vector3& w) const override;

    Shape* shape=nullptr;
};


#endif //BOUNCE_LIGHT_HPP
