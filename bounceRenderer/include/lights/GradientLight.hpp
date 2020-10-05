//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_GRADIENTLIGHT_HPP
#define BOUNCE_GRADIENTLIGHT_HPP

#include "core/Light.hpp"
#include "lights/EnvironmentLight.hpp"


class GradientLight : public EnvironmentLight {
public:
    GradientLight() :
            EnvironmentLight(Color(0.4f, 0.6f, 1.0f), 1.0f),
            horizonColor(1.0f, 1.0f, 1.0f) {}
    explicit GradientLight(const float &i) :
            EnvironmentLight(Color(0.4f, 0.6f, 1.0f), i),
            horizonColor(1.0f, 1.0f, 1.0f) {}
    GradientLight(const Color &sky, const Color &horizon, const float& i) :
            EnvironmentLight(sky, i),
            horizonColor(horizon) {}

    Color getInfiniteIllumination(const Ray &ray) const override;

    Color horizonColor;
};


#endif //BOUNCE_GRADIENTLIGHT_HPP
