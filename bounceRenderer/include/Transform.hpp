//
// Created by Thomas Vallentin on 18/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCERENDERER_TRANSFORM_HPP
#define BOUNCERENDERER_TRANSFORM_HPP

#include "Matrix.hpp"
#include "vector3.h"


class Transform
{
public:
    Transform() = default;
    Transform(const Transform &other) : objectToWorld(other.objectToWorld), worldToObject(other.worldToObject) {}
    explicit Transform(const Matrix4 &mat) : objectToWorld(mat), worldToObject(mat.getInversed()) {}
    explicit Transform(const Matrix4 &mat, const Matrix4 &inv) : objectToWorld(mat), worldToObject(inv) {}

    Transform getInversed() const;

    Matrix4 objectToWorld, worldToObject;
};


static const Transform IdentityTransform(IdentityMatrix);

#endif //BOUNCERENDERER_TRANSFORM_HPP
