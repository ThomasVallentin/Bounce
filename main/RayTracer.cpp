#include <fstream>
#include <iostream>

#include "RayTracer.h"
#include "mathUtils.h"

vector3 defaultColor(const Ray& ray) {
	vector3 unit_direction = ray.direction().unitVector();
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vector3(1.0, 1.0, 1.0) + t * vector3(0.5, 0.7, 1.0);
}

vector3 unitToColor(const vector3& vec) {
	return vector3(vec.r() * 255.9, vec.g() * 255.9, vec.b() * 255.9);
}

bool RayTracer::trace(const Camera& camera)
{
	cout << "Tracing scene composed of " << m_world.list().size() << " hitables..." << endl;

	// opening file stream
	ofstream outputStream(m_outpath);

	// Write ppm format data
	outputStream << "P3\n" << m_width << " " << m_height << "\n255\n";

	// Progress bar
	int progress_bar = 0;

	// TODO: on inverse l'ecriture des pixels pour le ppm, 
	//       c'est pas propre, il faut trouver une solution
	for (int y = m_height - 1; y >= 0; y--) {
		for (int x = 0; x < m_width; x++) {
			vector3 outColor(0, 0, 0);
			
			for (int s = 0; s < m_samples; s++) {
				// cout << randomFlt() << endl;
				float urand = randomFlt();
				float vrand = randomFlt();
				float u = float(x + urand) / m_width;
				float v = float(y + vrand) / m_height;
				// cout << u << " " << v << endl;
				Ray ray = generatePrimaryRay(camera, u, v);
				
				outColor += computeRay(ray);
			}
			// Dividing the total of light received by all the sampled rays by the amount of samples
			outColor /= float(m_samples);

			// 0.0 to 1.0 -> 0 to 255
			outColor = unitToColor(outColor);

			outputStream << int(outColor.r()) << " " << int(outColor.g()) << " " << int(outColor.b()) << "\n";
	
		}

		if (int((1 - y / float(m_height)) *100) > progress_bar) {
			cout << "Rendering " << progress_bar << "%..." << endl;
			progress_bar += 5;
		}
	}

	outputStream.close();

	return true;
}


Ray RayTracer::generatePrimaryRay(const Camera& camera, float u, float v) const
{
	return Ray(camera.position, camera.lower_left_corner + u * camera.horizontal + v * camera.vertical);
}


Ray RayTracer::generateBouncingRay(const HitData& hitdata) const {
	vector3 point;
	do {
		point = 2.0 * vector3(randomFlt(), randomFlt(), randomFlt()) - vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);
	
	vector3 target = hitdata.normal + point;
	
	Ray ray(hitdata.position, target);

	return Ray(hitdata.position, target);
}


vector3 RayTracer::computeRay(const Ray& ray) const
{
	HitData hit;
	vector3 outColor;

	if (m_world.isHit(ray, m_near_clip, m_far_clip, hit))
	{
		// Recursively sending rays each time the ray hits an object.
		outColor = 0.5 * computeRay(generateBouncingRay(hit));

	}
	else {
		outColor = defaultColor(ray);
	}

	return outColor;
}