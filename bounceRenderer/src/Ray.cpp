#include "Ray.h"

std::ostream& operator<<(std::ostream& os, const Ray& r)
{
	os << "Ray(" << r.origin << " ; " << r.direction << ")";
	return os;
}
