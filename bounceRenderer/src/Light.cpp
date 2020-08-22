//
// Created by Thomas Vallentin on 19/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Light.hpp"


Color PointLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Vector3 toLight;
    Ray lightRay;

    toLight = sample() - hitdata.position;
    float lightDistance = toLight.length();

    lightRay.origin = hitdata.position;
    lightRay.direction = toLight.normalized();

    if (!scene->intersectAny(lightRay, 0.0001, lightDistance))
        return power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction))  / powf(lightDistance, 2);

    return Color::Black();
}

Point3 PointLight::sample() const {
    return Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]);
}
