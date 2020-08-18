//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Color.hpp"

Color &Color::operator+=(const Color &col) {
    r += col.r ; g += col.g ; b += col.b ; a += col.a ;
    return *this;
}

Color &Color::operator-=(const Color &col) {
    r -= col.r ; g -= col.g ; b -= col.b ; a -= col.a ;
    return *this;
}

Color &Color::operator*=(const Color &col) {
    r *= col.r ; g *= col.g ; b *= col.b ; a *= col.a ;
    return *this;
}

Color &Color::operator/=(const Color &col) {
    r /= col.r ; g /= col.g ; b /= col.b ; a /= col.a ;
    return *this;
}

Color &Color::operator*=(float f) {
    r *= f ; g *= f ; b *= f ; a *= f ;
    return *this;
}

Color &Color::operator/=(float f) {
    r /= f ; g /= f ; b /= f ; a /= f;
    return *this;
}

Color Color::operator+(const Color &col) const {
    return Color(r + col.r,
                 g + col.g,
                 b + col.b,
                 a + col.a);
}

Color Color::operator-(const Color &col) const {
    return Color(r - col.r,
                 g - col.g,
                 b - col.b,
                 a - col.a);}

Color Color::operator*(const Color &col) const {
    return Color(r * col.r,
                 g * col.g,
                 b * col.b,
                 a * col.a);
}

Color Color::operator/(const Color &col) const {
    return Color(r / col.r,
                 g / col.g,
                 b / col.b,
                 a / col.a);
}

Color Color::operator*(float f) const {
    return Color(r * f,
                 g * f,
                 b * f,
                 a * f);
}

Color Color::operator/(float f) const {
    return Color(r / f,
                 g / f,
                 b / f,
                 a / f);
}

std::istream &operator>>(std::istream &is, Color &col) {
    is >> col.r >> col.g >> col.b >> col.a;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Color &col) {
    os << "Point3(" << col.r << ", " << col.g << ", " << col.b << ", " << col.a << ")";
    return os;
}
