//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/DirectionalLight.hpp"


Color DirectionalLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Ray lightRay;

    lightRay.origin = hitdata.position;
    lightRay.direction = toLight;
    if (!scene->intersectAny(lightRay, 0.0001, 9999999))
        return power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction));

    return Color::Black();
}