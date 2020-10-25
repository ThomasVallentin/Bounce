//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "lights/DiscLight.hpp"


Color DiscLight::lightEmitted(const HitData &hitdata, const Vector3 &w) const {
    return (dot(hitdata.normal, w) > 0) ? power() / shape->area() : Color::Black();
}
