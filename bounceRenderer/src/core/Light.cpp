//
// Created by Thomas Vallentin on 19/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "core/Light.hpp"
#include "materials/Incandescent.hpp"

Color AreaLight::sample(const HitData &hitdata, Vector3 &wi, Point3 &sampleP, float &pdf) const {
    HitData sample = shape->sampleFromPoint(hitdata, pdf);
    if (pdf == 0)
        return Color::Black();

    wi = (sample.position - hitdata.position);
    sampleP = sample.position;

    Color L = lightEmitted(sample, -wi) / powf(wi.length(), decay);
    wi.normalize();

    return L;
}

AreaLight::AreaLight(const Transform *transform, const int &lightSamples, Shape *shape) :
        Light(transform),
        shape(shape) {
    samples = lightSamples;
    shape->material = new IncandescentMaterial(this);
}

AreaLight::AreaLight(const Transform *transform, const Color &c, const float &i, const int &samples, Shape *shape) :
        Light(transform, c, i, samples),
        shape(shape) {
    shape->material = new IncandescentMaterial(this);
}

float AreaLight::computePdf(const HitData &hitdata, const Vector3 &w) const {
    return shape->samplePdf(hitdata);
}
