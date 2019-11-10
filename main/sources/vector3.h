#include <iostream>
#include <math.h>

class vector3 {
public:
	vector3() {}
	vector3(float v0, float v1, float v2) {
		v[0] = v0; 
		v[1] = v1; 
		v[2] = v2; }

	float x() const { return v[0]; }
	float y() const { return v[1]; }
	float z() const { return v[2]; }

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

	float v[3];
};