#ifndef HITABLEH
#define HITABLEH

#include "Shader.h"

class Hitable {

public:
	virtual bool isHit(const Ray& ray, float tmin, float tmax, HitData& data) const = 0;
	// The "= 0" at the end means that the function is purely virtual
    std::string name;
	Shader* shader_ptr;
};


#endif