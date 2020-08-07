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
        point = 2.0 * Vector3(randomFlt(), randomFlt(), 0.0f)  - Vector3(1, 1, 0);
    } while (point.squaredLength() >= 1.0);

    return point;
}

Vector3 randPointInUnitSphere() {
	Vector3 point;
	do {
		point = 2.0 * Vector3(randomFlt(), randomFlt(), randomFlt()) - Vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);

	return point;
}
