//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_COLOR_HPP
#define BOUNCE_COLOR_HPP

#include <iostream>


class Color {
public:
    Color() {
        c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
    }
    Color(const float &f) {
        for (float &i : c)
            i = f;
    }
    Color(const float &vr, const float &vg, const float &vb) {
        c[0]=vr ; c[1]=vg ; c[2]=vb ; c[3]=1.0f ;
    }
    Color(const float &vr, const float &vg, const float &vb, const float &va) {
        c[0]=vr ; c[1]=vg ; c[2]=vb ; c[3]=va ;
    }
    Color(const Color& col) {
        c[0]=col.r() ; c[1]=col.g() ; c[2]=col.b(); c[3]=col.a(); }

    float r() const { return c[0]; }
    float g() const { return c[1]; }
    float b() const { return c[2]; }
    float a() const { return c[3]; }

    float operator[](int i) const { return c[i]; }
    float& operator[](int i) { return c[i]; }

    Color operator+() { return *this; }
    Color operator-() { return Color(-c[0], -c[1], -c[2], -c[3]); }

    Color& operator+=(const Color &col);
    Color& operator-=(const Color &col);
    Color& operator*=(const Color &col);
    Color& operator/=(const Color &col);
    Color& operator*=(float f);
    Color& operator/=(float f);

    Color operator+(const Color& col) const;
    Color operator-(const Color& col) const;
    Color operator*(const Color& col) const;
    Color operator*(float f) const;
    Color operator/(const Color& col) const;
    Color operator/(float f) const;

private:
    float c[4]{};
};

extern
extern
extern
extern

extern
extern
extern

extern std::istream& operator>>(std::istream& is, Color& col);
extern std::ostream& operator<<(std::ostream& os, const Color& col);


#endif //BOUNCE_COLOR_HPP
