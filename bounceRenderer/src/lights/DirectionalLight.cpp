//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/DirectionalLight.hpp"


Color DirectionalLight::sample(const HitData &hitdata, Vector3 &wi, Point3 &sampleP, float &pdf) const {
    wi = toLight;
    sampleP = Point3(toLight * 100000);
    pdf = 1;

    return power();
}

