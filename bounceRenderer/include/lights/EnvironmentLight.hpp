//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_ENVIRONMENTLIGHT_HPP
#define BOUNCE_ENVIRONMENTLIGHT_HPP


#include "Light.hpp"


class EnvironmentLight : public Light {
public:
    EnvironmentLight() : Light() {}
    EnvironmentLight(const Color& c, const float& i) : Light() { color = c; intensity = i; }
    Color getInfiniteIllumination(const Ray& ray) const override;
};

#endif //BOUNCE_ENVIRONMENTLIGHT_HPP
