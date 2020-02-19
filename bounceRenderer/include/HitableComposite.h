#ifndef HITABLECOMPOSITEH
#define HITABLECOMPOSITEH

#include "Hitable.h"
#include <vector>

class HitableComposite : public Hitable {

public:
	HitableComposite() = default;
	HitableComposite(std::vector<Hitable*> l, std::string n) { m_hitableList = l; name = n; }

	const std::vector<Hitable*> list() { return m_hitableList; };
	void addHitable(Hitable* h) { m_hitableList.push_back(h); }

	bool isHit(const Ray& ray, float tmin, float tmax, HitData& data) const override ;

private:
    std::vector<Hitable*> m_hitableList;
};

#endif