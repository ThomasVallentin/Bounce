#ifndef RAYH
#define RAYH

#include "vector3.h"

class Ray {

public:
	Ray() {}
	Ray(const vector3& o, const vector3& d) { m_origin = o; m_direction = d.unitVector(); }

	vector3 origin() const { return m_origin; }
	vector3 direction() const { return m_direction; }
	vector3 pointAtParameter(float t) const { return m_origin + t * m_direction; }

private:
	vector3 m_origin;
	vector3 m_direction;
};

struct HitData {
	double t;
	vector3 position;
	vector3 normal;
};

#endif