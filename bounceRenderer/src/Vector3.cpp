#include "Vector3.hpp"

// == General Operators =================================================================

Vector3 operator+(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.x() + vec2.x(), vec1.y() + vec2.y(), vec1.z() + vec2.z());
}

Vector3 operator-(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.x() - vec2.x(), vec1.y() - vec2.y(), vec1.z() - vec2.z());
}

Vector3 operator*(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.x() * vec2.x(), vec1.y() * vec2.y(), vec1.z() * vec2.z());
}

Vector3 operator/(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.x() / vec2.x(), vec1.y() / vec2.y(), vec1.z() / vec2.z());
}

Vector3 operator*(const Vector3& vec, float f) {
	return Vector3(vec.x() * f, vec.y() * f, vec.z() * f);
}

Vector3 operator*(float f, const Vector3& vec) {
	return Vector3(vec.x() * f, vec.y() * f, vec.z() * f);
}

Vector3 operator/(const Vector3& vec, float f) {
	return Vector3(vec.x() / f, vec.y() / f, vec.z() / f);
}

std::istream& operator>>(std::istream& is, Vector3& vec)
{
	is >> vec[0] >> vec[1] >> vec[2];
	return is;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << "Vector3(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
	return os;
}

// == Constructors ======================================================================

Vector3::Vector3(const float &v0, const float &v1, const float &v2) { v[0]=v0; v[1]=v1; v[2]=v2; }

// == Self Operators ====================================================================

Vector3& Vector3::operator+=(const Vector3& vec2)
{
	v[0] += vec2.v[0];
	v[1] += vec2.v[1];
	v[2] += vec2.v[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec2)
{
	v[0] -= vec2.v[0];
	v[1] -= vec2.v[1];
	v[2] -= vec2.v[2];
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec2)
{
	v[0] *= vec2.v[0];
	v[1] *= vec2.v[1];
	v[2] *= vec2.v[2];
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& vec2)
{
	v[0] /= vec2.v[0];
	v[1] /= vec2.v[1];
	v[2] /= vec2.v[2];
	return *this;
}

Vector3& Vector3::operator*=(const float f)
{
	v[0] *= f;
	v[1] *= f;
	v[2] *= f;
	return *this;
}

Vector3& Vector3::operator/=(const float f)
{
	v[0] /= f;
	v[1] /= f;
	v[2] /= f;
	return *this;
}

// == Math Methods ======================================================================

float dot(const Vector3& vec1, const Vector3& vec2) {
	return vec1.x() * vec2.x() + vec1.y() * vec2.y() + vec1.z() * vec2.z();
}

Vector3 cross(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.y() * vec2.z() - vec1.z() * vec2.y(),
		vec1.z() * vec2.x() - vec1.x() * vec2.z(),
		vec1.x() * vec2.y() - vec1.y() * vec2.x());
}

void Vector3::normalize()
{
	float len = length();
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}

Vector3 Vector3::normalized() const {
	return Vector3(v[0], v[1], v[2]) / length(); }



Vector3 reflectVector(const Vector3& v, const Vector3& n) {
	return v - 2 * dot(v, n) * n;
}