//
// Created by Thomas Vallentin on 19/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Light.hpp"


Color PointLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Vector3 toLight;
    Ray lightRay;

    toLight = Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]) - hitdata.position;
    float lightDistance = toLight.length();

    lightRay.origin = hitdata.position;
    lightRay.direction = toLight.normalized();

    if (!scene->intersectAny(lightRay, 0.0001, lightDistance))
        return power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction))  / powf(lightDistance, 2);

    return Color::Black();
}

Color EnvironmentLight::getInfiniteIllumination(const Ray &ray) const {
    return power();
}

Color DirectionalLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Ray lightRay(hitdata.position, Vector3(t->matrix.m[2][0], t->matrix.m[2][1], t->matrix.m[2][2]) * -1);

    if (!scene->intersectAny(lightRay, 0.0001, 9999999))
        return power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction));

    return Color::Black();
}
