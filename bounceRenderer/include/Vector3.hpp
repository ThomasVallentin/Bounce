#ifndef VECTOR3H
#define VECTOR3H

#include <cmath>
#include <iostream>
#include <sstream> 
#include <string>

class Matrix4;
class Transform;
class Point3;

class Vector3 {

public:
	Vector3() { x = y = z = 0.0f;}
	Vector3(const float &v0, const float &v1, const float &v2);
	Vector3(const Vector3& vec)  { x=vec.x ; y=vec.y ; z=vec.z; }
    Vector3(const Point3 &pt);

	float operator[](const unsigned int& i) { float array[]{x, y, z}; return array[i]; }

	Vector3 operator+() { return *this; }
	Vector3 operator-() { return Vector3(-x, -y, -z); }

	Vector3& operator+=(const Vector3 &vec2);
	Vector3& operator-=(const Vector3 &vec2);
	Vector3& operator*=(const Vector3 &vec2);
	Vector3& operator/=(const Vector3 &vec2);
	Vector3& operator*=(float f);
	Vector3& operator/=(float f);
    Vector3& operator*=(const Matrix4& mat);
    Vector3& operator*=(const Transform& trans);

    Vector3 operator+(const Vector3& vec2) const;
    Vector3 operator-(const Vector3& vec2) const;

    Vector3 operator*(const Vector3& vec2)  const;
    Vector3 operator*(float f)  const;
    Vector3 operator/(const Vector3& vec2)  const;
    Vector3 operator/(float f)  const;
    Vector3 operator*(const Matrix4& mat)  const;
    Vector3 operator*(const Transform& trans)  const;

	float squaredLength() const { return x * x + y * y + z * z; }
	float length() const { return sqrtf( squaredLength() ); }
	void normalize();
	Vector3 normalized() const;

	float x, y, z;
};

extern float dot(const Vector3& vec1, const Vector3& vec2);
extern Vector3 cross(const Vector3& vec1, const Vector3& vec2);
extern Vector3 reflectVector(const Vector3& v, const Vector3& n);

extern std::istream& operator>>(std::istream& is, Vector3& vec);
extern std::ostream& operator<<(std::ostream& os, const Vector3& vec);

#endif