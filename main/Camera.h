#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

class Camera
{
public:
	Camera() {
		position = vector3(0.0, 0.0, 0.0);
		horizontal = vector3(4.0, 0.0, 0.0);
		vertical = vector3(0.0, 2.0, 0.0);
		lower_left_corner = vector3(-2.0, -1.0, -1.0);
	}

	vector3 position;
	vector3 horizontal;
	vector3 vertical;
	vector3 lower_left_corner;
};

#endif