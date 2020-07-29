#ifndef HITABLECOMPOSITEH
#define HITABLECOMPOSITEH

#include "Hitable.h"

#include <vector>

class HitableComposite : public Hitable {

public:
	HitableComposite() = default;
	explicit HitableComposite(std::vector<Hitable*> l) { m_hitableList = l; }

	std::vector<Hitable*> list() { return m_hitableList; };
	void addHitable(Hitable* h) { m_hitableList.push_back(h); }

	bool intersect(const Ray& ray, float tmin, float tmax, HitData& data) const override ;

protected:
    std::vector<Hitable*> m_hitableList;
};

#endif