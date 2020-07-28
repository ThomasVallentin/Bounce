//
// Created by Thomas Vallentin on 19/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCERENDERER_MATRIX_HPP
#define BOUNCERENDERER_MATRIX_HPP

#include "vector3.h"

#include <cmath>
#include <iostream>

class Matrix4 {
public:
    Matrix4() {
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] =
        m[1][2] = m[1][3] = m[2][0] = m[2][1] =
        m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
    }
    Matrix4(const float (&mat)[4][4]);
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);
    Matrix4(const Matrix4& other);


    void set(const float (&mat)[4][4]);
    void set(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);

    void inverse();
    Matrix4 getInversed() const;
    void transpose();
    Matrix4 getTransposed() const;
    Matrix4 getCofactorMatrix() const;
    float determinant();
    bool isIdentity();

    float m[4][4];
    bool operator==(const Matrix4 &other);
};

const static Matrix4 IdentityMatrix(1,0,0,0,
                                    0,1,0,0,
                                    0,0,1,0,
                                    0,0,0,1);

#endif //BOUNCERENDERER_MATRIX_HPP
