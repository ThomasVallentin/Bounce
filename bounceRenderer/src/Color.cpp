//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Color.hpp"

Color &Color::operator+=(const Color &col) {
    c[0] += col[0] ; c[1] += col[1] ; c[2] += col[2] ; c[3] += col[3] ;
    return *this;
}

Color &Color::operator-=(const Color &col) {
    c[0] -= col[0] ; c[1] -= col[1] ; c[2] -= col[2] ; c[3] -= col[3] ;
    return *this;
}

Color &Color::operator*=(const Color &col) {
    c[0] *= col[0] ; c[1] *= col[1] ; c[2] *= col[2] ; c[3] *= col[3] ;
    return *this;
}

Color &Color::operator/=(const Color &col) {
    c[0] /= col[0] ; c[1] /= col[1] ; c[2] /= col[2] ; c[3] /= col[3] ;
    return *this;
}

Color &Color::operator*=(float f) {
    c[0] *= f ; c[1] *= f ; c[2] *= f ; c[3] *= f ;
    return *this;
}

Color &Color::operator/=(float f) {
    c[0] /= f ; c[1] /= f ; c[2] /= f ; c[3] /= f;
    return *this;
}

Color operator+(const Color &col1, const Color &col2) {
    return Color(col1[0] + col2[0],
                 col1[1] + col2[1],
                 col1[2] + col2[2],
                 col1[3] + col2[3]);
}

Color operator-(const Color &col1, const Color &col2) {
    return Color(col1[0] - col2[0],
                 col1[1] - col2[1],
                 col1[2] - col2[2],
                 col1[3] - col2[3]);}

Color operator*(const Color &col1, const Color &col2) {
    return Color(col1[0] * col2[0],
                 col1[1] * col2[1],
                 col1[2] * col2[2],
                 col1[3] * col2[3]);
}

Color operator/(const Color &col1, const Color &col2) {
    return Color(col1[0] / col2[0],
                 col1[1] / col2[1],
                 col1[2] / col2[2],
                 col1[3] / col2[3]);
}

Color operator*(const Color &col, float f) {
    return Color(col[0] * f,
                 col[1] * f,
                 col[2] * f,
                 col[3] * f);
}

Color operator*(float f, const Color &col) {
    return Color(col[0] * f,
                 col[1] * f,
                 col[2] * f,
                 col[3] * f);
}

Color operator/(const Color &col, float f) {
    return Color(col[0] / f,
                 col[1] / f,
                 col[2] / f,
                 col[3] / f);
}

std::istream &operator>>(std::istream &is, Color &col) {
    is >> col[0] >> col[1] >> col[2];
    return is;
}

std::ostream &operator<<(std::ostream &os, const Color &col) {
    os << "Point3(" << col[0] << ", " << col[1] << ", " << col[2] << ")";
    return os;
}
