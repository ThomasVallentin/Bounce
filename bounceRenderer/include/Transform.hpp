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
    Transform(Matrix4 &mat) : worldMatrix(mat), inverseWorldMatrix(mat.getInversed()) {}

    Matrix4 worldMatrix, inverseWorldMatrix;
};


#endif //BOUNCERENDERER_TRANSFORM_HPP
