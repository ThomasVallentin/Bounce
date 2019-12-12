#ifndef HITABLECOMPOSITEH
#define HITABLECOMPOSITEH

#include "Sphere.h"
#include <vector>

class HitableComposite : public Hitable {

public:
	HitableComposite() {}
	HitableComposite(vector<Hitable*> l, string n) { m_hitableList = l; name = n; }

	const vector<Hitable*> list() { return m_hitableList; };
	void addHitable(Hitable* h) { m_hitableList.push_back(h); }

	virtual bool isHit(const Ray& ray, float tmin, float tmax, HitData& data) const;

private:
	vector<Hitable*> m_hitableList;
};

#endif