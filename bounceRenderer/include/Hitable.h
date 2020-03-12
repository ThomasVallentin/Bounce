#ifndef HITABLEH
#define HITABLEH

#include "Shader.h"

class Hitable {

public:
    Hitable() : shader_ptr(nullptr) {}
	virtual bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;
	// The "= 0" at the end means that the function is purely virtual
	Shader* shader_ptr;
};


#endif