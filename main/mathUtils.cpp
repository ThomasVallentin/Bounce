#include "mathUtils.h"

float randomFlt(float a, float b) {
	float random = float(rand()) / float(RAND_MAX);
	float diff = b - a;
	return random * diff + a;
}

vector3 randPointInUnitSphere() {
	vector3 point;
	do {
		point = 2.0 * vector3(randomFlt(), randomFlt(), randomFlt()) - vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);

	return point;
}
