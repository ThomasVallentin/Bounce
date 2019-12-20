#include "vector3.h"

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

istream& operator>>(istream& is, vector3& vec)
{
	is >> vec.v[0] >> vec.v[1] >> vec.v[2];
	return is;
}

ostream& operator<<(ostream& os, const vector3& vec)
{
	os << vec.v[0] << " " << vec.v[1] << " " << vec.v[2];
	return os;
}

// == Constructors ======================================================================

vector3::vector3(float v0, float v1, float v2) { v[0]=v0; v[1]=v1; v[2]=v2; }

vector3::vector3(const vector3& vec) { v[0]=vec.v[0] ; v[1]=vec.v[1] ; v[2]=vec.v[2]; }

// == Self Operators ====================================================================

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

// == Math Methods ======================================================================

float dot(const vector3& vec1, const vector3& vec2) {
	return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

vector3 cross(const vector3& vec1, const vector3& vec2) {
	return vector3(vec1.y() * vec2.z() - vec1.z() * vec2.y(),
		vec1.z() * vec2.x() - vec1.x() * vec2.z(),
		vec1.x() * vec2.y() - vec1.y() * vec2.x());
}

void vector3::normalize()
{
	float len = length();
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}

vector3 vector3::unitVector() const {
	return vector3(v[0], v[1], v[2]) / length(); }

vector3 reflectVector(const vector3& v, const vector3& n) {
	return v - 2 * dot(v, n) * n;
}