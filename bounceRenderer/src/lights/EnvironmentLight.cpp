//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/EnvironmentLight.hpp"

Color EnvironmentLight::getInfiniteIllumination(const Ray &ray) const {
    return power();
}