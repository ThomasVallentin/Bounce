#include "Ray.h"

ostream& operator<<(ostream& os, const Ray& r)
{
	os << "Ray(o=" << r.origin() << ";d=" << r.direction() << ")"; 
	return os;
}
