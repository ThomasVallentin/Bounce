#include "vector3.h"


vector3 operator+(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.v[0] + vec2.v[0], vec1.v[1] + vec2.v[1], vec1.v[2] + vec2.v[2]);
}

vector3 operator-(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.v[0] - vec2.v[0], vec1.v[1] - vec2.v[1], vec1.v[2] - vec2.v[2]);
}

vector3 operator*(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.v[0] * vec2.v[0], vec1.v[1] * vec2.v[1], vec1.v[2] * vec2.v[2]);
}

vector3 operator/(const vector3& vec1, const vector3 vec2) {
	return vector3(vec1.v[0] / vec2.v[0], vec1.v[1] / vec2.v[1], vec1.v[2] / vec2.v[2]);
}

vector3 operator*(const vector3& vec, float f) {
	return vector3(vec.v[0] * f, vec.v[1] * f, vec.v[2] * f);
}

vector3 operator*(float f, const vector3& vec) {
	return vector3(vec.v[0] * f, vec.v[1] * f, vec.v[2] * f);
}

vector3 operator/(const vector3& vec, float f) {
	return vector3(vec.v[0] / f, vec.v[1] / f, vec.v[2] / f);
}

vector3& vector3::operator+=(const vector3& vec2)
{
	v[0] += vec2.v[0];
	v[1] += vec2.v[1];
	v[2] += vec2.v[2];
	return *this;
}

vector3& vector3::operator-=(const vector3& vec2)
{
	v[0] -= vec2.v[0];
	v[1] -= vec2.v[1];
	v[2] -= vec2.v[2];
	return *this;
}

vector3& vector3::operator*=(const vector3& vec2)
{
	v[0] *= vec2.v[0];
	v[1] *= vec2.v[1];
	v[2] *= vec2.v[2];
	return *this;
}

vector3& vector3::operator/=(const vector3& vec2)
{
	v[0] /= vec2.v[0];
	v[1] /= vec2.v[1];
	v[2] /= vec2.v[2];
	return *this;
}

vector3& vector3::operator*=(const float f)
{
	v[0] *= f;
	v[1] *= f;
	v[2] *= f;
	return *this;
}

vector3& vector3::operator/=(const float f)
{
	v[0] /= f;
	v[1] /= f;
	v[2] /= f;
	return *this;
}

void vector3::normalize()
{
	float len = length();
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}

vector3 vector3::unitVector()
{
	return *this / length();
}

float dot(const vector3& vec1, const vector3& vec2) {
	return vec1.v[0]*vec2.v[0] + vec1.v[1]*vec2.v[1] + vec1.v[2]*vec2.v[2];
}

vector3 cross(const vector3& vec1, const vector3& vec2) {
	return vector3(vec1.v[1]*vec2.v[2] - vec1.v[2]*vec2.v[1],
				   vec1.v[2]*vec2.v[0] - vec1.v[0]*vec2.v[2], 
				   vec1.v[0]*vec2.v[1] - vec1.v[1]*vec2.v[0]);
}