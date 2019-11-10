#ifndef VECTOR3H
#define VECTOR3H

#include <iostream>
#include <math.h>

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

class vector3 {
public:
	vector3() {}
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
	vector3& operator*=(const float f);
	vector3& operator/=(const float f);

	float squaredLength() {
		return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	float length() {
		return sqrt(this->squaredLength()); }
	void normalize();
	vector3 unitVector();

private:
	float v[3];
};

// == Utils Functions ===================================================================

float dot(const vector3& vec1, const vector3& vec2) {
	return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

vector3 cross(const vector3& vec1, const vector3& vec2) {
	return vector3(vec1.y() * vec2.z() - vec1.z() * vec2.y(),
		vec1.z() * vec2.x() - vec1.x() * vec2.z(),
		vec1.x() * vec2.y() - vec1.y() * vec2.x());
}

// == General Operators =================================================================

vector3 operator+(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.x() + vec2.x(), vec1.y() + vec2.y(), vec1.z() + vec2.z());
}

vector3 operator-(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.x() - vec2.x(), vec1.y() - vec2.y(), vec1.z() - vec2.z());
}

vector3 operator*(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.x() * vec2.x(), vec1.y() * vec2.y(), vec1.z() * vec2.z());
}

vector3 operator/(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.x() / vec2.x(), vec1.y() / vec2.y(), vec1.z() / vec2.z());
}

vector3 operator*(const vector3& vec, float f) {
	return vector3(vec.x() * f, vec.y() * f, vec.z() * f);
}

vector3 operator*(float f, const vector3& vec) {
	return vector3(vec.x() * f, vec.y() * f, vec.z() * f);
}

vector3 operator/(const vector3& vec, float f) {
	return vector3(vec.x() / f, vec.y() / f, vec.z() / f);
}

#endif