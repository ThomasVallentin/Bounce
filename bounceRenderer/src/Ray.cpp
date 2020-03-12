#include "Ray.h"

std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(o=" << r.origin << ";d=" << r.direction << ")";
	return os;
}
