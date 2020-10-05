//
// Created by Thomas Vallentin on 19/03/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "core/Matrix.hpp"


float ** createMatrix(const int size)
{
    float **matrix = new float* [size];
    for (int i=0 ; i < size ; i++)
        matrix[i] = new float[size];

    return matrix;
}

void deleteMatrix(float **matrix, const int size)
{
    for (int j=0 ; j < size ; j++) {
        delete[] matrix[j];
    }
    delete[] matrix;
}

void makeComatrix(float **mat, const int i, const int j, float **com, const int N)
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


float matrixDeterminant(float **mat, const int N)
{
    // Determinant is obtained by summing recursively the determinants of each one of its first row's coMatrices.
    if (N <= 1) {
//        std::cout << mat[0][0] << std::endl;
        return mat[0][0];
    }
    float **comatrix = createMatrix(N-1);

    int sign(1);
    float det(0);
    for (int i=0 ; i < N ; i++)
    {
        makeComatrix(mat, 0, i, comatrix, N);
        det += float(sign) * mat[0][i] * matrixDeterminant(comatrix, N-1);

        sign *= -1;
    }

    // Free matrix memory
    deleteMatrix(comatrix, N-1);

    return det;
}


void cofactorMatrix(float **mat, float **cof, const int N)
{
    // CoFactorMatrix == each cell is equal to the determinant of the base matrix's coMatrix
    int startSign(1), sign;

    float **comatrix = createMatrix(N-1);

    // For each cell of the matrix, compute its comatrix determinant & set it in the same cell of the new matrix
    for (int i=0 ; i < N ; i++)
    {
        sign = startSign;
        for (int j=0 ; j < N ; j++) {
            makeComatrix(mat, i, j, comatrix, N);
            cof[i][j] = matrixDeterminant(comatrix, N-1) * float(sign);

            sign *= -1;
        }
        startSign *= -1;

    }

    deleteMatrix(comatrix, N-1);
}


void transposeMatrix(float **mat, float **trans, const int N)
{
    // Invert the x and y values of the cells (cell [2, 4] becomes the cell [4, 2])
    // It causes the matrix to be mirrored from its "topLeft-bottomRight" diagonal
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            trans[i][j] = mat[j][i];
        }
    }
}


void adjugateMatrix(float **mat, float **adj, const int N)
{
    // Adjugate matrix == transposed cofactor matrix
    float **temp = createMatrix(N);
    cofactorMatrix(mat, temp, N);
    transposeMatrix(temp, adj, N);
}


bool inverseMatrix(float **mat, float **inv, const int N)
{
    // Inverse matrix == 1/det * adjugateMatrix
    float det = matrixDeterminant(mat, N);
    if (det == 0)
        return false;

    adjugateMatrix(mat, inv, N);

    for (int i=0 ; i < N ; i++)
    {
        for (int j=0 ; j < N ; j++)
        {
            inv[i][j] /= det;
        }
    }

    return true;
};


float **multMatrix(float **mat, float **other, const int size)
{
    float **mult = createMatrix(size);

    float tmp;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            tmp = 0;
            for (int n = 0; n < size; n++) {
                tmp += mat[i][n] * other[n][j];
            }
            mult[i][j] = tmp;
        }

    return mult;
}

Matrix4::Matrix4(float **mat) {
    m = createMatrix(4);
    set(mat);
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
                 float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
    m = createMatrix(4);
    set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
}


Matrix4::Matrix4(const Matrix4 &other) {
    m = createMatrix(4);
    set(other.m);
}


void Matrix4::set(float **mat)
{
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
    float **inv = createMatrix(4);
    inverseMatrix(m, inv, 4);
    set(inv);
}


Matrix4 Matrix4::getInversed() const {
    float **inv = createMatrix(4);
    inverseMatrix(m, inv, 4);
    return Matrix4(inv);
}


void Matrix4::transpose() {
    float **trans = createMatrix(4);
    transposeMatrix(m, trans, 4);
    set(trans);
}


Matrix4 Matrix4::getTransposed() const {
    float **trans = createMatrix(4);
    transposeMatrix(m, trans, 4);
    return Matrix4(trans);
}


Matrix4 Matrix4::getCofactorMatrix() const {
    float **cof = createMatrix(4);
    cofactorMatrix(m, cof, 4);
    return Matrix4(cof);
}


float Matrix4::determinant() {
    return matrixDeterminant(m, 4);
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

Matrix4::Matrix4(const float (&mat)[4][4]) {
    m = createMatrix(4);
    for (int i=0 ; i < 4 ; i++)
        for (int j=0 ; j < 4 ; j++)
            m[i][j] = mat[i][j];
}

Matrix4 operator*(const Matrix4 &mat, const Matrix4 &other) {
    Matrix4 res;
    res.m = multMatrix(mat.m, other.m, 4);
    return res;
}

Matrix4 &Matrix4::operator*=(const Matrix4 &other) {
    float **tmp = multMatrix(m, other.m, 4);
    deleteMatrix(m, 4);
    m = tmp;
    return *this;
}

Matrix4::~Matrix4() {
    deleteMatrix(m, 4);
}


Vector3 Vector3::operator*(const Matrix4& mat) const
{
    return Vector3(mat.m[0][0] * x + mat.m[1][0] * y + mat.m[2][0] * z,
                   mat.m[0][1] * x + mat.m[1][1] * y + mat.m[2][1] * z,
                   mat.m[0][2] * x + mat.m[1][2] * y + mat.m[2][2] * z);
}

Vector3 &Vector3::operator*=(const Matrix4 &mat) {
    float temp[3]{mat.m[0][0] * x + mat.m[1][0] * y + mat.m[2][0] * z,
                  mat.m[0][1] * x + mat.m[1][1] * y + mat.m[2][1] * z,
                  mat.m[0][2] * x + mat.m[1][2] * y + mat.m[2][2] * z};
    x = temp[0];
    y = temp[1];
    z = temp[2];

    return *this;
}


Point3 Point3::operator*(const Matrix4& mat) const
{
    return Point3(mat.m[0][0] * x + mat.m[1][0] * y + mat.m[2][0] * z + mat.m[3][0],
                  mat.m[0][1] * x + mat.m[1][1] * y + mat.m[2][1] * z + mat.m[3][1],
                  mat.m[0][2] * x + mat.m[1][2] * y + mat.m[2][2] * z + mat.m[3][2]);
}

Point3 &Point3::operator*=(const Matrix4 &mat) {
    float temp[3]{mat.m[0][0] * x + mat.m[1][0] * y + mat.m[2][0] * z,
                  mat.m[0][1] * x + mat.m[1][1] * y + mat.m[2][1] * z,
                  mat.m[0][2] * x + mat.m[1][2] * y + mat.m[2][2] * z};
    x = temp[0];
    y = temp[1];
    z = temp[2];

    return *this;
}