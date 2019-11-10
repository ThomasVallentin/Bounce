#ifndef VECTOR3H
#define VECTOR3H

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

extern float dot(const vector3& vec1, const vector3& vec2);
extern vector3 cross(const vector3& vec1, const vector3& vec2);

extern vector3 operator+(const vector3& vec1, const vector3 vec2);
extern vector3 operator-(const vector3& vec1, const vector3 vec2);
extern vector3 operator*(const vector3& vec1, const vector3 vec2);
extern vector3 operator/(const vector3& vec1, const vector3 vec2);

extern vector3 operator*(const vector3& vec, float f);
extern vector3 operator*(float f, const vector3& vec);
extern vector3 operator/(const vector3& vec, float f);

#endif