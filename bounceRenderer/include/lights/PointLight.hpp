//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_POINT_HPP
#define BOUNCE_POINT_HPP

#include "Light.hpp"

class PointLight : public Light {
public:
    PointLight() : Light() {}
    explicit PointLight(const Transform *worldToLight) : Light(worldToLight) {}
    PointLight(const Transform *worldToLight, const Color &c, const float &i) : Light(worldToLight, c, i) {}

    Color getIllumination(const HitData &hitdata, Scene *scene) const override;
};



#endif //BOUNCE_POINT_HPP
