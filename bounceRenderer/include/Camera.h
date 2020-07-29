#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

class Camera
{
public:
	Camera() {
		position = vector3(0.0, 2.2, 1.3);
		horizontal = vector3(2.0, 0.0, 0.0);
		vertical = vector3(0.0, 1.0, 0.0);
        top_left_corner = vector3(-1.0, 0.33, -1.7);
	}

	vector3 position;
	vector3 horizontal;
	vector3 vertical;
	vector3 top_left_corner;
};

#endif