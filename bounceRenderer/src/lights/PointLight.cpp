//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/PointLight.hpp"


Color PointLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Vector3 toLight;
    Ray lightRay;

    toLight = Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]) - hitdata.position;
    float lightDistance = toLight.length();

    lightRay.origin = hitdata.position;
    lightRay.direction = toLight.normalized();

    if (!scene->intersectAny(lightRay, 0.0001, lightDistance)) {
        return power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction)) / powf(lightDistance, 2);
    }

    return Color::Black();
}
