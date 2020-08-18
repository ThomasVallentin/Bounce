//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_POINT3_HPP
#define BOUNCE_POINT3_HPP

#include "Vector3.hpp"

class Point3 {
public:
    Point3() { p[0] = p[1] = p[2] = 0.0f;}
    Point3(const float x, const float y, const float z) { p[0] = x; p[1] = y; p[2] = z; }
    Point3(const Point3 &point) { p[0] = point[0]; p[1] = point[1]; p[2] = point[2]; }
    Point3(const Vector3 &vec) { p[0] = vec[0]; p[1] = vec[1]; p[2] = vec[2]; }

    float x() const { return p[0]; }
    float y() const { return p[1]; }
    float z() const { return p[2]; }

    Point3 operator+() { return *this; }
    Point3 operator-() { return Point3(-p[0], -p[1], -p[2]); }
    float operator[](int i) const { return p[i]; }
    float& operator[](int i) { return p[i]; }

    Point3& operator+=(const Vector3 &vec2);
    Point3& operator-=(const Vector3 &vec2);
    Point3& operator*=(const Vector3 &vec2);
    Point3& operator/=(const Vector3 &vec2);
    Point3& operator*=(float f);
    Point3& operator/=(float f);
    Point3& operator*=(const Matrix4& mat);
    Point3& operator*=(const Transform& trans);

    Point3 operator+(const Point3& p2) const;
    Point3 operator+(const Vector3& vec) const;
    Point3 operator-(const Point3& p2) const;
    Point3 operator-(const Vector3& vec) const;

    Point3 operator*(float f) const;
    Point3 operator*(const Matrix4& mat) const;
    Point3 operator*(const Transform& trans) const;
    Point3 operator/(float f) const;

    Point3 vectorTo(const Point3 &point);
private:
    float p[3] = {};
};

extern std::istream& operator>>(std::istream& is, Point3& pt);
extern std::ostream& operator<<(std::ostream& os, const Point3& pt);


#endif //BOUNCE_POINT3_HPP
