//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/DirectionalLight.hpp"


Color DirectionalLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Ray lightRay(hitdata.position, Vector3(t->matrix.m[2][0], t->matrix.m[2][1], t->matrix.m[2][2]) * -1);

    if (!scene->intersectAny(lightRay, 0.0001, 9999999))
        return power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction));

    return Color::Black();
}