#ifndef MATHUTILSH
#define MATHUTILSH

#include <math.h>
#include <stdlib.h>

float randomFlt(float a = 0, float b = 1) {
	float random = float(rand()) / float(RAND_MAX);
	float diff = b - a;
	return random * diff + a;
}

#endif