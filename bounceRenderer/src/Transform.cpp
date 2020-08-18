//
// Created by Thomas Vallentin on 18/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Transform.hpp"


Transform Transform::getInversed() {
    return Transform(inverseMatrix, matrix);
}

void Transform::translate(const Vector3 &t) {
    matrix.m[3][0] += t.x();
    matrix.m[3][1] += t.y();
    matrix.m[3][2] += t.z();
    inverseMatrix.m[3][0] -= t.x();
    inverseMatrix.m[3][1] -= t.y();
    inverseMatrix.m[3][2] -= t.z();
}

void Transform::translate(const float x, const float y, const float z) {
    matrix.m[3][0] += x;
    matrix.m[3][1] += y;
    matrix.m[3][2] += z;
    inverseMatrix.m[3][0] -= x;
    inverseMatrix.m[3][1] -= y;
    inverseMatrix.m[3][2] -= z;
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

void Transform::scale(const float x, const float y, const float z) {
    Matrix4 tmp(x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1);
    matrix *= tmp;
    inverseMatrix = matrix.getInversed();
}

Transform *Transform::LookAt(const Vector3 &from, const Vector3 &to, bool reversed) {
    Vector3 front;
    if (reversed)
        front = Vector3(from - to);
    else
        front = Vector3(to - from);

    front = front.normalized();

    Vector3 side(cross(Vector3(0, 1, 0), front));
    side.normalize();

    Vector3 up(cross(front, side));
    up.normalize();

    Matrix4 mat(side.x(), side.y(), side.z(), 0,
                up.x(), up.y(), up.z(), 0,
                front.x(), front.y(), front.z(), 0,
                from.x(), from.y(), from.z(), 1);

    static Transform trans(mat, mat.getInversed());
    return &trans;
}

Transform *Transform::LookAt(Transform *from, Transform *to, bool reversed) {
    return LookAt(Vector3(from->matrix.m[3][0], from->matrix.m[3][1], from->matrix.m[3][2]),
                  Vector3(to->matrix.m[3][0], to->matrix.m[3][1], to->matrix.m[3][2]),
                  reversed);
}

Vector3 Transform::translateVector(const Vector3 &pos) const {
    return pos + Vector3( matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]);
}




Vector3 operator*(const Vector3& vec, const Transform& trans)
{
    return Vector3(trans.matrix.m[0][0] * vec.x() + trans.matrix.m[1][0] * vec.y() + trans.matrix.m[2][0] * vec.z(),
                   trans.matrix.m[0][1] * vec.x() + trans.matrix.m[1][1] * vec.y() + trans.matrix.m[2][1] * vec.z(),
                   trans.matrix.m[0][2] * vec.x() + trans.matrix.m[1][2] * vec.y() + trans.matrix.m[2][2] * vec.z());
}

Vector3& Vector3::operator*=(const Transform &trans)
{
    float temp[3]{trans.matrix.m[0][0] * v[0] + trans.matrix.m[1][0] * v[1] + trans.matrix.m[2][0] * v[2],
                  trans.matrix.m[0][1] * v[0] + trans.matrix.m[1][1] * v[1] + trans.matrix.m[2][1] * v[2],
                  trans.matrix.m[0][2] * v[0] + trans.matrix.m[1][2] * v[1] + trans.matrix.m[2][2] * v[2]};
    v[0] = temp[0];
    v[1] = temp[1];
    v[2] = temp[2];

    return *this;
}


Point3 operator*(const Point3& pt, const Transform& trans)
{
    return Point3(trans.matrix.m[0][0] * pt.x() + trans.matrix.m[1][0] * pt.y() + trans.matrix.m[2][0] * pt.z(),
                  trans.matrix.m[0][1] * pt.x() + trans.matrix.m[1][1] * pt.y() + trans.matrix.m[2][1] * pt.z(),
                  trans.matrix.m[0][2] * pt.x() + trans.matrix.m[1][2] * pt.y() + trans.matrix.m[2][2] * pt.z());
}


Point3& Point3::operator*=(const Transform &trans)
{
    float temp[3]{trans.matrix.m[0][0] * p[0] + trans.matrix.m[1][0] * p[1] + trans.matrix.m[2][0] * p[2] + trans.matrix.m[3][0],
                  trans.matrix.m[0][1] * p[0] + trans.matrix.m[1][1] * p[1] + trans.matrix.m[2][1] * p[2] + trans.matrix.m[3][0],
                  trans.matrix.m[0][2] * p[0] + trans.matrix.m[1][2] * p[1] + trans.matrix.m[2][2] * p[2] + trans.matrix.m[3][0]};
    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];

    return *this;
}