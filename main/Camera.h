#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"

class Camera
{
public:
	Camera() {
		m_position = vector3(0.0, 0.0, 0.0);
		m_horizontal = vector3(4.0, 0.0, 0.0);
		m_vertical = vector3(0.0, 2.0, 0.0);
		m_lower_left_corner = vector3(-2.0, -1.0, -1.0);
	}

	Ray generateRay(float u, float v) const { return Ray(m_position, m_lower_left_corner + u * m_horizontal + v * m_vertical); }

private:
	vector3 m_position;
	vector3 m_horizontal;
	vector3 m_vertical;
	vector3 m_lower_left_corner;
};

#endif