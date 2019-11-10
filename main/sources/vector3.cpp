#include "vector3.h"

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