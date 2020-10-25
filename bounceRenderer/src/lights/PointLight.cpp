//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/PointLight.hpp"


Color PointLight::sample(const HitData &hitdata, Vector3 &wi, Point3 &sampleP, float &pdf) const {
    sampleP = Point3(t->matrix.m[3][0], t->matrix.m[3][1], t->matrix.m[3][2]);
    wi = sampleP - hitdata.position;
    pdf = 1;

    Color L = power() / powf(wi.length(), decay);
    wi.normalize();

    return L;
}
