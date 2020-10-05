//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "core/Point3.hpp"


Vector3::Vector3(const Point3 &pt) {
    x = pt.x ; y = pt.y ; z = pt.z;
}

Point3 &Point3::operator+=(const Point3 &pt) {
    x += pt.x;
    y += pt.y;
    z += pt.z;
    return *this;
}

Point3& Point3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Point3 &Point3::operator-=(const Point3 &pt) {
    x -= pt.x;
    y -= pt.y;
    z -= pt.z;
    return *this;
}

Point3& Point3::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Point3& Point3::operator*=(const float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Point3& Point3::operator/=(const float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Point3 Point3::operator+(const Point3 &pt) const {
    return Point3(x + pt.x, y + pt.y, z + pt.z);
}

Point3 Point3::operator+(const Vector3 &vec) const {
    return Point3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Point3::operator-(const Point3 &pt) const {
    return Point3(x - pt.x, y - pt.y, z - pt.z);
}

Point3 Point3::operator-(const Vector3 &vec) const {
    return Point3(x - vec.x, y - vec.y, z - vec.z);
}

Point3 Point3::operator*(float f) const {
    return Point3(x * f, y * f, z * f);
}

Point3 Point3::operator/(float f) const {
    return Point3(x / f, y / f, z / f);
}

std::istream& operator>>(std::istream& is, Point3& pt)
{
    is >> pt.x >> pt.y >> pt.z;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point3& pt)
{
    os << "Point3(" << pt.x << ", " << pt.y << ", " << pt.z << ")";
    return os;
}
