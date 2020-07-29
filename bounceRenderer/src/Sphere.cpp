#include "Sphere.h"

bool Sphere::intersect(const Ray& ray, float tmin, float tmax, HitData& hit) const
{
	// std::cout << ray.origin << " " << ray.direction << std::endl;
	vector3 centerToOrigin = ray.origin - m_center;
	float a = dot(ray.direction, ray.direction); // optim : =1 if direction is normalized
	float b = 2 * dot(centerToOrigin, ray.direction);
	float c = dot(centerToOrigin, centerToOrigin) - m_radius * m_radius;

	// Quadratic resolution of f(t) = (origin - center + direction*t) - radius**2 = 0
	float discr = b * b - 4 * a * c;
	if (discr > 0) {

		// Warning: possible loss of precision here due to the float precision
		// -> go check scratchapixel -> ray sphere intersection

		float t = float(-b - sqrt(discr)) / (2.0 * a);
		if (tmin < t && t < tmax) {
			// ray hits the first side of the sphere
			hit.t = t;
			hit.position = ray.pointAtParameter(t);
			hit.normal = (hit.position - center());
			hit.normal.normalize();
			hit.shader_ptr = shader;
			return true;
		}

		t = float(-b + sqrt(discr)) / (2.0 * a);
		if (tmin < t && t < tmax) {
			// ray hits the second side of the sphere (the camera is inside the sphere)
			hit.t = t;
			hit.position = ray.pointAtParameter(t);
			hit.normal = (hit.position - center()) / radius();
			hit.shader_ptr = shader;
			return true;
		}
	}
	return false; // does not hit
}
