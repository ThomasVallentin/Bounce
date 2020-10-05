#include "core/Vector3.hpp"

// == General Operators =================================================================

Vector3 Vector3::operator+(const Vector3& vec) const {
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const {
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator*(const Vector3& vec) const {
	return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

Vector3 Vector3::operator/(const Vector3& vec) const {
	return Vector3(x / vec.x, y / vec.y, z / vec.z);
}

Vector3 Vector3::operator*(float f) const {
	return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(float f) const {
	return Vector3(x / f, y / f, z / f);
}

std::istream& operator>>(std::istream& is, Vector3& vec)
{
	is >> vec.x >> vec.y >> vec.z;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return os;
}

// == Constructors ======================================================================

Vector3::Vector3(const float &v0, const float &v1, const float &v2) { x = v0 ; y = v1 ; z = v2 ; }

// == Self Operators ====================================================================

Vector3& Vector3::operator+=(const Vector3& vec2)
{
	x += vec2.x;
	y += vec2.y;
	z += vec2.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec2)
{
	x -= vec2.x;
	y -= vec2.y;
	z -= vec2.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec2)
{
	x *= vec2.x;
	y *= vec2.y;
	z *= vec2.z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& vec2)
{
	x /= vec2.x;
	y /= vec2.y;
	z /= vec2.z;
	return *this;
}

Vector3& Vector3::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector3& Vector3::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

// == Math Methods ======================================================================

float dot(const Vector3& vec1, const Vector3& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector3 cross(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x);
}

void Vector3::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
}

Vector3 Vector3::normalized() const {
	return Vector3(x, y, z) / length();
}

Vector3 reflectVector(const Vector3& v, const Vector3& n) {
	return v - n * 2 * dot(v, n);
}