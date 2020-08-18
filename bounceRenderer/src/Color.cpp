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

Color Color::operator+(const Color &col) const {
    return Color(r() + col[0],
                 g() + col[1],
                 b() + col[2],
                 a() + col[3]);
}

Color Color::operator-(const Color &col) const {
    return Color(r() - col[0],
                 g() - col[1],
                 b() - col[2],
                 a() - col[3]);}

Color Color::operator*(const Color &col) const {
    return Color(r() * col[0],
                 g() * col[1],
                 b() * col[2],
                 a() * col[3]);
}

Color Color::operator/(const Color &col) const {
    return Color(r() / col[0],
                 g() / col[1],
                 b() / col[2],
                 a() / col[3]);
}

Color Color::operator*(float f) const {
    return Color(r() * f,
                 g() * f,
                 b() * f,
                 a() * f);
}

Color Color::operator/(float f) const {
    return Color(r() / f,
                 g() / f,
                 b() / f,
                 a() / f);
}

std::istream &operator>>(std::istream &is, Color &col) {
    is >> col[0] >> col[1] >> col[2];
    return is;
}

std::ostream &operator<<(std::ostream &os, const Color &col) {
    os << "Point3(" << col[0] << ", " << col[1] << ", " << col[2] << ")";
    return os;
}
