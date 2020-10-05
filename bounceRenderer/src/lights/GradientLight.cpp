//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/GradientLight.hpp"

Color GradientLight::getInfiniteIllumination(const Ray &ray) const {
    float a = std::min(ray.direction.y * 5.0f, 1.0f);

    if (ray.direction.y < 0)
        a *= -1;

    return (color * a + horizonColor * (1 - a)) * intensity;
}
