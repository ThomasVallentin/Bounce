#ifndef RAYH
#define RAYH

#include "core/Vector3.hpp"
#include "core/Point3.hpp"
#include "core/Color.hpp"
#include "core/Material.hpp"
#include <iostream>


class BSDF;

class Ray {

public:
	Ray() = default;
	Ray(const Vector3& o, const Vector3& d) { origin = o; direction = d.normalized(); }

	Point3 pointAtParameter(float t) const { return origin + direction * t; }

    Point3 origin;
    Vector3 direction;
};

extern std::ostream& operator<<(std::ostream& os, const Ray& r);

struct HitData {
	Ray generateRay(const Vector3 &direction) { return Ray(position, direction); }

	void computeScattering() {
        if (material)
            material->computeScattering(*this);
    }

    Color getEmission() {
		if (material)
			return material->getEmission(*this, wo);
		return Color::Black();
	}

    ~HitData();

    double t;
    Point3 position;
    Vector3 wo, normal;
    Vector3 tan1, tan2;
    Material* material=nullptr;
    BSDF* bsdf=nullptr;
};

#endif
