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
	Vector3() { v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f;}
	Vector3(const float &v0, const float &v1, const float &v2);
	Vector3(const Vector3& vec)  { v[0]=vec.v[0] ; v[1]=vec.v[1] ; v[2]=vec.v[2]; }
    Vector3(const Point3 &point);

	float x() const { return v[0]; }
	float y() const { return v[1]; }
	float z() const { return v[2]; }

	Vector3 operator+() { return *this; }
	Vector3 operator-() { return Vector3(-v[0], -v[1], -v[2]); }
	float operator[](int i) const { return v[i]; }
	float& operator[](int i) { return v[i]; }
	
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

	float squaredLength() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	float length() const { return sqrtf(this->squaredLength()); }
	void normalize();
	Vector3 normalized() const;

private:
	float v[3] = {};
};

extern float dot(const Vector3& vec1, const Vector3& vec2);
extern Vector3 cross(const Vector3& vec1, const Vector3& vec2);
extern Vector3 reflectVector(const Vector3& v, const Vector3& n);

extern std::istream& operator>>(std::istream& is, Vector3& vec);
extern std::ostream& operator<<(std::ostream& os, const Vector3& vec);

#endif