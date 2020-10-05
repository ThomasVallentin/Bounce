//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_COLOR_HPP
#define BOUNCE_COLOR_HPP

#include <iostream>
#include <cmath>

class Color {
public:
    Color() {
        r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
    }
    Color(const float &f) {
        r = g = b = f;
        a = 1.0f;
    }
    Color(const float &vr, const float &vg, const float &vb) {
        r = vr ; g = vg ; b = vb ; a = 1.0f ;
    }
    Color(const float &vr, const float &vg, const float &vb, const float &va) {
        r = vr ; g = vg ; b = vb ; a = va ;
    }
    Color(const Color& col) {
        r = col.r ; g = col.g ; b = col.b ; a = col.a; }

    float operator[](const unsigned int& i) { float array[]{r, g, b}; return array[i]; }


    Color operator+() { return *this; }
    Color operator-() { return Color(-r, -g, -b, -a); }

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

    static Color Black() { return Color(0.0f, 0.0f, 0.0f); };
    static Color Red() { return Color(1.0f, 0.0f, 0.0f); };
    static Color Green() { return Color(0.0f, 1.0f, 0.0f); };
    static Color Blue() { return Color(0.0f, 0.0f, 1.0f); };

    bool isBlack() const { return (r == 0 && g == 0 && b == 0 ); }

    float r, g, b, a;
};



extern std::istream& operator>>(std::istream& is, Color& col);
extern std::ostream& operator<<(std::ostream& os, const Color& col);

extern Color colorfToColor8(const Color& col);
extern Color applyGamma(const Color& color, float gamma);
extern float applyGamma(const float& color, float gamma);


#endif //BOUNCE_COLOR_HPP
