//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_POINT3_HPP
#define BOUNCE_POINT3_HPP

#include "Vector3.hpp"

class Point3 {
public:
    Point3() { x = y = z = 0.0f;}
    Point3(const float px, const float py, const float pz) { x = px; y = py; z = pz; }
    Point3(const Point3 &point) { x = point.x; y = point.y; z = point.z; }
    Point3(const Vector3 &vec) { x = vec.x ; y = vec.y ; z = vec.z; }

    float operator[](const unsigned int& i) { float array[]{x, y, z}; return array[i]; }

    Point3 operator+() { return *this; }
    Point3 operator-() { return Point3(-x, -y, -z); }

    Point3& operator+=(const Point3 &pt);
    Point3& operator+=(const Vector3 &vec2);
    Point3& operator-=(const Point3 &pt);
    Point3& operator-=(const Vector3 &vec2);
    Point3& operator*=(float f);
    Point3& operator/=(float f);
    Point3& operator*=(const Matrix4& mat);
    Point3& operator*=(const Transform& trans);

    Point3 operator+(const Point3& p2) const;
    Point3 operator+(const Vector3& vec) const;
    Vector3 operator-(const Point3& p2) const;
    Point3 operator-(const Vector3& vec) const;

    Point3 operator*(float f) const;
    Point3 operator*(const Matrix4& mat) const;
    Point3 operator*(const Transform& trans) const;
    Point3 operator/(float f) const;

    float x, y, z;
};

extern std::istream& operator>>(std::istream& is, Point3& pt);
extern std::ostream& operator<<(std::ostream& os, const Point3& pt);


#endif //BOUNCE_POINT3_HPP
