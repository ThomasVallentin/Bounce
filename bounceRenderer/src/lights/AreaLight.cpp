//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/AreaLight.hpp"


Color DiscLight::getIllumination(const HitData &hitdata, Scene *scene) const {
    Color illumination = Color::Black();
    Point3 lightHitPoint;
    Vector3 toLight, lightNormal(t->matrix.m[2][0], t->matrix.m[2][1], t->matrix.m[2][2]);
    Ray lightRay;
    float lightDistance;

    lightRay.origin = hitdata.position;
    for (size_t i=0 ; i < samples ; i++) {
        lightHitPoint = Point3(randPointInUnitCircle()) * radius;
        lightHitPoint = lightHitPoint * *t;

        toLight = lightHitPoint - hitdata.position;
        lightDistance = toLight.length();

        lightRay.direction = toLight.normalized();

        if (!scene->intersectAny(lightRay, 0.0001, lightDistance)) {

            illumination += power() * std::max(0.0f, dot(hitdata.normal, lightRay.direction)) * std::max(0.0f, dot(lightNormal, lightRay.direction)) / powf(lightDistance, 2);
        }
    }
    return illumination / samples;
}

bool DiscLight::intersect(const Ray &ray, float tmin, float tmax, HitData &data) const {
    float parameter;
    Vector3 lightNormal(t->matrix.m[2][0], t->matrix.m[2][1], t->matrix.m[2][2]);

    if (!intersectDisk(ray, lightNormal, radius,
                       Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]), parameter))
        return false;

    if (parameter <= tmin || parameter >= tmax)
        return false;

    data.position = ray.origin + ray.direction * parameter;
    data.normal = lightNormal;
    data.shader = shader;
    data.t = parameter;

    return true;
}
