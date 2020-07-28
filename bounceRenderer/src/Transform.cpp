//
// Created by Thomas Vallentin on 18/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Transform.hpp"


vector3 operator*(const vector3& vec, const Transform& trans)
{
   return vector3(trans.objectToWorld.m[0][0] * vec.x() + trans.objectToWorld.m[1][0] * vec.y() + trans.objectToWorld.m[2][0] * vec.z() + trans.objectToWorld.m[3][0] * 1,
                  trans.objectToWorld.m[0][1] * vec.x() + trans.objectToWorld.m[1][1] * vec.y() + trans.objectToWorld.m[2][1] * vec.z() + trans.objectToWorld.m[3][1] * 1,
                  trans.objectToWorld.m[0][2] * vec.x() + trans.objectToWorld.m[1][2] * vec.y() + trans.objectToWorld.m[2][2] * vec.z() + trans.objectToWorld.m[3][2] * 1);
}

vector3& vector3::operator*=(const Transform &trans)
{
    float temp[3]{trans.objectToWorld.m[0][0] * v[0] + trans.objectToWorld.m[1][0] * v[1] + trans.objectToWorld.m[2][0] * v[2] + trans.objectToWorld.m[3][0] * 1,
                  trans.objectToWorld.m[0][1] * v[0] + trans.objectToWorld.m[1][1] * v[1] + trans.objectToWorld.m[2][1] * v[2] + trans.objectToWorld.m[3][1] * 1,
                  trans.objectToWorld.m[0][2] * v[0] + trans.objectToWorld.m[1][2] * v[1] + trans.objectToWorld.m[2][2] * v[2] + trans.objectToWorld.m[3][2] * 1};
    v[0] = temp[0];
    v[1] = temp[1];
    v[2] = temp[2];
}

Transform Transform::getInversed() const {
    return Transform(worldToObject, objectToWorld);
}
