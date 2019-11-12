#include "Sphere.h"

float Sphere::isHit(const Ray& ray) const
{
	//cout << ray.origin() << " " << ray.direction() << endl;
	vector3 centerToOrigin = ray.origin() - m_center;
	float a = dot(ray.direction(), ray.direction()); // optim : =1 if direction is normalized 
	float b = 2 * dot(centerToOrigin, ray.direction());
	float c = dot(centerToOrigin, centerToOrigin) - m_radius * m_radius;

	// Quadratic resolution of f(t) = (origin - center + direction*t) - radius**2 = 0
	float discr = b * b - 4 * a * c;
	if (discr < 0) {
		return -1.0; // does not hit
	}
	else {
		float res = (-b + sqrt(discr)) / (2.0*a);
		return (-b - sqrt(discr)) / (2.0 * a); // hit at t = -0.5 * (b + sqrt(discr)) / a
		// possible loss of precision here due to the float precision
		// -> go check scratchapixel -> ray sphere intersection
	}
}
