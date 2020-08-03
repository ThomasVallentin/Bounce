//
// Created by Thomas Vallentin on 18/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Transform.hpp"


vector3 operator*(const vector3& vec, const Transform& trans)
{
   return vector3(trans.matrix.m[0][0] * vec.x() + trans.matrix.m[1][0] * vec.y() + trans.matrix.m[2][0] * vec.z() + trans.matrix.m[3][0] * 1,
                  trans.matrix.m[0][1] * vec.x() + trans.matrix.m[1][1] * vec.y() + trans.matrix.m[2][1] * vec.z() + trans.matrix.m[3][1] * 1,
                  trans.matrix.m[0][2] * vec.x() + trans.matrix.m[1][2] * vec.y() + trans.matrix.m[2][2] * vec.z() + trans.matrix.m[3][2] * 1);
}

vector3& vector3::operator*=(const Transform &trans)
{
    float temp[3]{trans.matrix.m[0][0] * v[0] + trans.matrix.m[1][0] * v[1] + trans.matrix.m[2][0] * v[2] + trans.matrix.m[3][0] * 1,
                  trans.matrix.m[0][1] * v[0] + trans.matrix.m[1][1] * v[1] + trans.matrix.m[2][1] * v[2] + trans.matrix.m[3][1] * 1,
                  trans.matrix.m[0][2] * v[0] + trans.matrix.m[1][2] * v[1] + trans.matrix.m[2][2] * v[2] + trans.matrix.m[3][2] * 1};
    v[0] = temp[0];
    v[1] = temp[1];
    v[2] = temp[2];

    return *this;
}

Transform Transform::getInversed() const {
    return Transform(inverseMatrix, matrix);
}

void Transform::translate(const vector3 &t) const {
    matrix.m[3][0] += t.x();
    matrix.m[3][1] += t.y();
    matrix.m[3][2] += t.z();
    inverseMatrix.m[3][0] -= t.x();
    inverseMatrix.m[3][1] -= t.y();
    inverseMatrix.m[3][2] -= t.z();
}

void Transform::translate(const float x, const float y, const float z) const {
    matrix.m[3][0] += x;
    matrix.m[3][1] += y;
    matrix.m[3][2] += y;
    inverseMatrix.m[3][0] -= x;
    inverseMatrix.m[3][1] -= y;
    inverseMatrix.m[3][2] -= y;
}

void Transform::rotate(const Axis axis, float rad) {
    if (axis == Axis::x)
    {
        Matrix4 tmp(1, 0, 0, 0,
                    0, cosf(rad), -sinf(rad), 0,
                    0, sinf(rad), cosf(rad), 0,
                    0, 0, 0, 1);
        matrix *= tmp;
        inverseMatrix = matrix.getInversed();

    } else if (axis == Axis::y) {
        Matrix4 tmp(cosf(rad), 0, -sinf(rad), 0,
                    0, 1, 0, 0,
                    sinf(rad), 0, cosf(rad), 0,
                    0, 0, 0, 1);
        matrix *= tmp;
        inverseMatrix = matrix.getInversed();

    } else if (axis == Axis::z) {
        Matrix4 tmp(cosf(rad), -sinf(rad), 0, 0,
                    sinf(rad), cosf(rad), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
        matrix *= tmp;
        inverseMatrix = matrix.getInversed();
    }
}
