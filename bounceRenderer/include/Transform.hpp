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
    Transform(const Transform &other) : matrix(other.matrix), inverseMatrix(other.inverseMatrix) {}
    explicit Transform(const Matrix4 &mat, const Matrix4 &inv) : matrix(mat), inverseMatrix(inv) {}

    Transform getInversed() const;

    Matrix4 matrix, inverseMatrix;
};


static const Transform IdentityTransform(IdentityMatrix, IdentityMatrix.getInversed());

#endif //BOUNCERENDERER_TRANSFORM_HPP
