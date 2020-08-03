#ifndef MATHUTILSH
#define MATHUTILSH

#define PI 3.14159265f

#include "vector3.h"
#include <cmath>
#include <cstdlib>

extern float degToRad(const float deg);
extern float radToDeg(const float rad);

extern float randomFlt(float a=0, float b=1);
extern vector3 randPointInUnitSphere();

#endif