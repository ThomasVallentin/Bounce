#include "mathUtils.h"
#include <random>

float randomFlt(float a, float b) {
	float rnd = float(random()) / float(RAND_MAX);
	float diff = b - a;
	return rnd * diff + a;
}

vector3 randPointInUnitSphere() {
	vector3 point;
	do {
		point = 2.0 * vector3(randomFlt(), randomFlt(), randomFlt()) - vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);

	return point;
}
