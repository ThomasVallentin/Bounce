//
// Created by Thomas Vallentin on 18/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCERENDERER_TRANSFORM_HPP
#define BOUNCERENDERER_TRANSFORM_HPP

#include "Matrix.hpp"
#include "vector3.h"

enum Axis{
    x,
    y,
    z
};

class Transform
{
public:
    Transform() = default;
    Transform(const Transform &other) : matrix(other.matrix), inverseMatrix(other.inverseMatrix) {}
    explicit Transform(const Matrix4 &mat, const Matrix4 &inv) : matrix(mat), inverseMatrix(inv) {}

    Transform getInversed();
    void translate(const float x, const float y, const float z);
    void translate(const vector3 &t);
    void rotate(const Axis axis, float rotation);
    void scale(const float x, const float y, const float z);

    static Transform *Identity() { return new Transform(IdentityMatrix, IdentityMatrix.getInversed()); }

    Matrix4 matrix, inverseMatrix;
};


#endif //BOUNCERENDERER_TRANSFORM_HPP
