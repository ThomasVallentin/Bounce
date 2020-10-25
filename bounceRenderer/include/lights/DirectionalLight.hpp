//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_DIRECTIONALLIGHT_HPP
#define BOUNCE_DIRECTIONALLIGHT_HPP

#include "core/Light.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight() : Light() {}
    explicit DirectionalLight(const Transform *transform) :
            Light(transform), toLight(t->matrix.m[2][0] * -1,
                                      t->matrix.m[2][1] * -1,
                                      t->matrix.m[2][2] * -1) {}
    DirectionalLight(const Transform *transform, const Color &c, const float &i) :
            Light(transform, c, i), toLight(t->matrix.m[2][0] * -1,
                                            t->matrix.m[2][1] * -1,
                                            t->matrix.m[2][2] * -1) {}

    Color sample(const HitData &hitdata, Vector3& wi, Point3 &sampleP, float &pdf) const override;
private:
    Vector3 toLight;
};

#endif //BOUNCE_DIRECTIONALLIGHT_HPP
