#ifndef VECTOR3H
#define VECTOR3H

#include <cmath>
#include <iostream>
#include <sstream> 
#include <string>

// +====================================================================================+
// | Vector3 :                                                                          | 
// +====================================================================================+
// |                                                                                    |
// |    This is the class responsible for all the math behind the rays and various      |
// | geometric calculations.                                                            |
// |                                                                                    |
// | Signatures:                                                                        |
// |    - float, float, float                                                           |
// |    - vector3                                                                       |
// |                                                                                    |
// +====================================================================================+
class Matrix4;
class Transform;


class vector3 {

public:
	vector3() { v[0] = 0.0; v[1] = 0.0; v[2] = 0.0;}
	vector3(float v0, float v1, float v2);
	vector3(const vector3& vec);

	float x() const { return v[0]; }
	float y() const { return v[1]; }
	float z() const { return v[2]; }
	float r() const { return v[0]; }
	float g() const { return v[1]; }
	float b() const { return v[2]; }

	vector3 operator+() { return *this; }
	vector3 operator-() { return vector3(-v[0], -v[1], -v[2]); }
	float operator[](int i) const { return v[i]; }
	float& operator[](int i) { return v[i]; }
	
	vector3& operator+=(const vector3 &vec2);
	vector3& operator-=(const vector3 &vec2);
	vector3& operator*=(const vector3 &vec2);
	vector3& operator/=(const vector3 &vec2);
	vector3& operator*=(float f);
	vector3& operator/=(float f);
    vector3& operator*=(const Matrix4& mat);
    vector3& operator*=(const Transform& trans);

	float squaredLength() const {
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	float length() const {
		return sqrt(this->squaredLength()); }
	void normalize();
	vector3 unitVector() const;

// private:
	float v[3]{};
};

extern float dot(const vector3& vec1, const vector3& vec2);
extern vector3 cross(const vector3& vec1, const vector3& vec2);
extern vector3 reflectVector(const vector3& v, const vector3& n);

extern vector3 operator+(const vector3& vec1, const vector3& vec2);
extern vector3 operator-(const vector3& vec1, const vector3& vec2);
extern vector3 operator*(const vector3& vec1, const vector3& vec2);
extern vector3 operator/(const vector3& vec1, const vector3& vec2);

extern vector3 operator*(const vector3& vec, float f);
extern vector3 operator*(float f, const vector3& vec);
extern vector3 operator/(const vector3& vec, float f);

extern vector3 operator*(const vector3& vec, const Matrix4& mat);
extern vector3 operator*(const vector3& vec, const Transform& trans);

extern std::istream& operator>>(std::istream& is, vector3& vec);
extern std::ostream& operator<<(std::ostream& os, const vector3& vec);


#endif