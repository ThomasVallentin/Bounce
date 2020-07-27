//
// Created by Thomas Vallentin on 19/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Matrix.hpp"

// This method is just here to avoid compiling errors caused by templates.
// Compiler estimate that N-1 can be less than 0 if N == 0 and its not possible which prevent the code to build.
// We just declare it to make a possible case where this goes fine.
template <std::size_t N>
void makeComatrix(float (&mat)[N][N], const int i, const int j, float (&com)[0][0]) {}

template <std::size_t N>
void makeComatrix(float (&mat)[N][N], const int i, const int j, float (&com)[N-1][N-1])
{

    if (N <= 1)
        return;

    int n(0), m(0);
    for (int a=0 ; a < N ; a++)
    {
        m = 0;
        if (a == i)
            continue;

        for (int b=0 ; b < N ; b++)
        {
            if (b == j)
                continue;
            com[n][m] = mat[a][b];
            m++;
        }
        n++;
    }
}


// This method is just here to avoid compiling errors caused by templates.
// Compiler estimate that N-1 can be less than 0 if N == 0 and its not possible which prevent the code to build.
// We just declare this to make a possible case where this goes fine.
float matrixDeterminant(float (&mat)[0][0]) {}

template <std::size_t N>
float matrixDeterminant(float (&mat)[N][N])
{
    // Determinant is gotter summing recursively the determinants of each on of its first row's coMatrices.
    if (N <= 1)
        return mat[0][0];

    int sign(1);
    float det(0);
    for (int i=0 ; i < N ; i++)
    {
        float comatrix[N-1][N-1];
        makeComatrix(mat, 0, i, comatrix);
        det += sign * mat[0][i] * matrixDeterminant(comatrix);

        sign *= -1;
    }

    return det;
}


template <std::size_t N>
void cofactorMatrix(float (&mat)[N][N], float cof[N][N])
{
    // CoFactorMatrix == each cell is equal to the determinant of the base matrix's coMatrix
    int startSign(1), sign;
    for (int i=0 ; i < N ; i++)
    {
        sign = startSign;
        for (int j=0 ; j < N ; j++) {
            float comatrix[N - 1][N - 1];
            makeComatrix(mat, i, j, comatrix);

            cof[i][j] = matrixDeterminant(comatrix) * sign;

            sign *= -1;
        }
        startSign *= -1;

    }
}


template <std::size_t N>
void transposeMatrix(float (&mat)[N][N], float (&trans)[N][N]) {
    // Invert the x and y values of the cells (cell [2, 4] becomes the cell [4, 2])
    // It causes the matrix to be mirrored from its "topLeft-bottomRight" diagonal
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            trans[i][j] = mat[j][i];
        }
    }
}


template <std::size_t N>
void adjugateMatrix(float (&mat)[N][N], float (&adj)[N][N])
{
    // Adjugate matrix == transposed cofactor matrix
    float temp[N][N];
    cofactorMatrix(mat, temp);
    transposeMatrix(temp, adj);
}


template <std::size_t N>
bool inverseMatrix(float (&mat)[N][N], float (&inv)[N][N])
{
    // Inverse matrix == 1/det * adjugateMatrix
    float det = matrixDeterminant(mat);
    if (det == 0)
        return false;

    adjugateMatrix(mat, inv);

    for (int i=0 ; i < N ; i++)
    {
        for (int j=0 ; j < N ; j++)
        {
            inv[i][j] /= det;
        }
    }

    return true;
};


Matrix4::Matrix4(float mat[4][4]) {
    set(mat);
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
                 float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
    set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
}


void Matrix4::set(float mat[4][4]) {
    m[0][0] = mat[0][0];    m[0][1] = mat[0][1];    m[0][2] = mat[0][2];    m[0][3] = mat[0][3];
    m[1][0] = mat[1][0];    m[1][1] = mat[1][1];    m[1][2] = mat[1][2];    m[1][3] = mat[1][3];
    m[2][0] = mat[2][0];    m[2][1] = mat[2][1];    m[2][2] = mat[2][2];    m[2][3] = mat[2][3];
    m[3][0] = mat[3][0];    m[3][1] = mat[3][1];    m[3][2] = mat[3][2];    m[3][3] = mat[3][3];
}


void Matrix4::set(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
                  float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
    m[0][0] = m00;    m[0][1] = m01;    m[0][2] = m02;    m[0][3] = m03;
    m[1][0] = m10;    m[1][1] = m11;    m[1][2] = m12;    m[1][3] = m13;
    m[2][0] = m20;    m[2][1] = m21;    m[2][2] = m22;    m[2][3] = m23;
    m[3][0] = m30;    m[3][1] = m31;    m[3][2] = m32;    m[3][3] = m33;
}


void Matrix4::inverse() {
    float inv[4][4];
    inverseMatrix(m, inv);
    set(inv);
}


Matrix4 Matrix4::getInversed() {
    float inv[4][4];
    inverseMatrix(m, inv);
    return Matrix4(inv);
}


void Matrix4::transpose() {
    float trans[4][4];
    transposeMatrix(m, trans);
    set(trans);
}


Matrix4 Matrix4::getTransposed() {
    float trans[4][4];
    transposeMatrix(m, trans);
    return Matrix4(trans);
}


Matrix4 Matrix4::getCofactorMatrix() {
    float cof[4][4];
    cofactorMatrix(m, cof);
    return Matrix4(cof);
}


float Matrix4::determinant() {
    return matrixDeterminant(m);
}


bool Matrix4::isIdentity() {
    return operator==(IdentityMatrix);
}


bool Matrix4::operator==(const Matrix4 &other) {
    for (int i=0 ; i < 4 ; i++)
        for (int j=0 ; j < 4 ; j++)
            if (m[i][j] != other.m[i][j])
                return false;

    return true;
}
