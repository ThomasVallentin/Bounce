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

vector3 randPointInUnitCircle() {
    vector3 point;
    do {
        point = 2.0 * vector3(randomFlt(), randomFlt(), 0.0f);
    } while (point.squaredLength() >= 1.0);

    return point;
}

vector3 randPointInUnitSphere() {
	vector3 point;
	do {
		point = 2.0 * vector3(randomFlt(), randomFlt(), randomFlt()) - vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);

	return point;
}
