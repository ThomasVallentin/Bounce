//
// Created by Thomas Vallentin on 07/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "Point3.hpp"


Vector3::Vector3(const Point3 &point) {
    v[0] = point[0]; v[1] = point[1]; v[2] = point[2];
}


Point3& Point3::operator+=(const Vector3& vec2)
{
    p[0] += vec2[0];
    p[1] += vec2[1];
    p[2] += vec2[2];
    return *this;
}

Point3& Point3::operator-=(const Vector3& vec2)
{
    p[0] -= vec2[0];
    p[1] -= vec2[1];
    p[2] -= vec2[2];
    return *this;
}

Point3& Point3::operator*=(const Vector3& vec2)
{
    p[0] *= vec2[0];
    p[1] *= vec2[1];
    p[2] *= vec2[2];
    return *this;
}

Point3& Point3::operator/=(const Vector3& vec2)
{
    p[0] /= vec2[0];
    p[1] /= vec2[1];
    p[2] /= vec2[2];
    return *this;
}

Point3& Point3::operator*=(const float f)
{
    p[0] *= f;
    p[1] *= f;
    p[2] *= f;
    return *this;
}

Point3& Point3::operator/=(const float f)
{
    p[0] /= f;
    p[1] /= f;
    p[2] /= f;
    return *this;
}

Point3 Point3::vectorTo(const Point3 &point) {
    return Point3(point[0] - p[0],
                  point[0] - p[1],
                  point[0] - p[2]);
}


std::istream& operator>>(std::istream& is, Point3& pt)
{
    is >> pt[0] >> pt[1] >> pt[2];
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point3& pt)
{
    os << "Point3(" << pt[0] << ", " << pt[1] << ", " << pt[2] << ")";
    return os;
}