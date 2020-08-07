#ifndef MATHUTILSH
#define MATHUTILSH

#define PI 3.14159265f

#include "Vector3.hpp"
#include <cmath>
#include <cstdlib>

extern float degToRad(const float deg);
extern float radToDeg(const float rad);

extern float randomFlt(float a=0, float b=1);
extern Vector3 randPointInUnitCircle();
extern Vector3 randPointInUnitSphere();

#endif