//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_POINT_HPP
#define BOUNCE_POINT_HPP

#include "core/Light.hpp"

class PointLight : public Light {
public:
    PointLight() : Light() {}

    explicit PointLight(const Transform *lightToWorld) : Light(lightToWorld) {}

    PointLight(const Transform *lightToWorld, const Color &c, const float &i) :
            Light(lightToWorld, c, i) {}

    Color sample(const HitData &hitdata, Vector3 &wi, Point3 &sampleP, float &pdf) const override;
};

#endif //BOUNCE_POINT_HPP
