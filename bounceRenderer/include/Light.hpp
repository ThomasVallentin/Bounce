//
// Created by Thomas Vallentin on 19/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_LIGHT_HPP
#define BOUNCE_LIGHT_HPP

#include "Color.hpp"
#include "TransformObject.hpp"


class Light : public TransformObject {
public:
    Light() : TransformObject(),
              intensity(1.0f),
              color(1.0f, 1.0f, 1.0f) {}

    Light(const Transform *worldToLight) : TransformObject(worldToLight),
                                           intensity(1.0f),
                                           color(1.0f, 1.0f, 1.0f) {}

    Light(const Transform *worldToLight, const Color &c, float &i) : TransformObject(worldToLight),
                                                                     intensity(i),
                                                                     color(c) {}

    Color getIllumination() const { return color * intensity; }
    virtual Point3 sample() const = 0;

    float intensity;
    Color color;
};


class PointLight : public Light {
    virtual Point3 sample() const { return Point3(t->matrix.m[3][0], t->matrix.m[3][3], t->matrix.m[3][2]); }
};

#endif //BOUNCE_LIGHT_HPP
