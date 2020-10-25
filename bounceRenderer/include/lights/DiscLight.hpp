//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_DISCLIGHT_HPP
#define BOUNCE_DISCLIGHT_HPP

#include "shapes/Disc.hpp"
#include "materials/Incandescent.hpp"
#include "core/Light.hpp"

class DiscLight : public AreaLight {
public:
    DiscLight(const Transform *transform, const float &radius) :
            AreaLight(transform, 2, new Disc(transform, radius)) {}

    DiscLight(const Transform *transform, const float &radius, const Color &c, const float &i, const int &samples) :
            AreaLight(transform, c, i, samples, new Disc(transform, radius)) {}

    Color lightEmitted(const HitData &hitdata, const Vector3 &w) const override;
};


#endif //BOUNCE_DISCLIGHT_HPP
