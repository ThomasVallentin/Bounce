#ifndef MATHUTILSH
#define MATHUTILSH

#define PI 3.14159265f

#include "Ray.h"
#include <cmath>
#include <cstdlib>

extern float degToRad(const float deg);
extern float radToDeg(const float rad);

extern float randomFlt(float a=0, float b=1);
extern Vector3 randPointInUnitCircle();
extern Vector3 randPointInUnitSphere();
extern bool intersectPlane(const Ray& ray, const Vector3& normal, const Point3& pointOnPlane, float& outParameter);
extern bool intersectDisk(const Ray& ray, const Vector3& normal, const float &radius, const Point3& center, float& outParameter);

#endif