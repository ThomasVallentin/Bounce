//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_DIRECTIONALLIGHT_HPP
#define BOUNCE_DIRECTIONALLIGHT_HPP

#include "Light.hpp"

class DirectionalLight : public Light {
public:
    DirectionalLight() : Light() {}
    explicit DirectionalLight(const Transform* transform) : Light(transform) {}
    DirectionalLight(const Transform* transform, const Color& c, const float& i) : Light(transform, c, i) {}

    Color getIllumination(const HitData &hitdata, Scene *scene) const override;
};

#endif //BOUNCE_DIRECTIONALLIGHT_HPP
