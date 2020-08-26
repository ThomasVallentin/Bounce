#include "mathUtils.h"

#include <random>

float degToRad(const float deg) {
    return PI / 180.0f  * deg;
}

float radToDeg(const float rad) {
    return rad * 180.0f / PI;
}

float randomFlt(float a, float b) {
	float rnd = float(rand()) / float(RAND_MAX);
	float diff = b - a;
	return rnd * diff + a;
}

Vector3 randPointInUnitCircle() {
    Vector3 point;
    do {
        point = Vector3(randomFlt(), randomFlt(), 0.0f) * 2.0f  - Vector3(1, 1, 0);
    } while (point.squaredLength() >= 1.0);

    return point;
}

Vector3 randPointInUnitSphere() {
	Vector3 point;
	do {
		point = Vector3(randomFlt(), randomFlt(), randomFlt()) * 2.0f - Vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);

	return point;
}

bool intersectPlane(const Ray& ray, const Vector3& normal, const Point3& pointOnPlane, float& outParameter) {
    float a = dot(normal, ray.direction);

    if (a < 0.000001)
        return false;

    Vector3 b(pointOnPlane - ray.origin);
    outParameter = dot(b, normal) / a;

    return outParameter >= 0;
}

bool intersectDisk(const Ray& ray, const Vector3& normal, const float& radius, const Point3& center, float& outParameter) {
    if (!intersectPlane(ray, normal, center, outParameter))
        return false;

    Vector3 centerToHit = center - (ray.origin + ray.direction * outParameter);
    return centerToHit.squaredLength() <= (radius * radius);
}