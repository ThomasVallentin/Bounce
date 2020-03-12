#include "HitableComposite.h"

bool HitableComposite::intersect(const Ray& ray, float tmin, float tmax, HitData& data) const
{
	double closest_so_far = tmax;
	bool hit_anything = false;
	HitData temp_data;
	
	// std::cout << "tracing pixel with " << m_hitableList.size() << std::endl;
	for (int i = 0; i < m_hitableList.size(); i++) {
		// cout << m_hitableList[i] << endl;
		if (m_hitableList[i]->intersect(ray, tmin, closest_so_far, temp_data)) {
			hit_anything = true;
			closest_so_far = temp_data.t;
			data = temp_data;
		}

	}
	return hit_anything;
}
