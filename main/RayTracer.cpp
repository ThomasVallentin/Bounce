#include <fstream>
#include <iostream>

#include "RayTracer.h"


vector3 defaultColor(const Ray& ray) {
	vector3 unit_direction = ray.direction().unitVector();
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vector3(1.0, 1.0, 1.0) + t * vector3(0.5, 0.7, 1.0);
}

vector3 unitToColor(const vector3& vec) {
	return vector3(vec.r() * 255.9, vec.g() * 255.9, vec.b() * 255.9);
}

vector3 applyGamma(const vector3& color, float gamma) {
	float factor = 1 / gamma;

	return vector3(pow(color[0], factor), pow(color[1], factor), pow(color[2], factor));
}

bool RayTracer::trace(const Camera& camera)
{
	cout << "Tracing scene composed of " << m_world.list().size() << " hitables..." << endl;

	// opening file stream
	cout << m_outpath << endl;
	ofstream outputStream(m_outpath);

	// Write ppm format data
	outputStream << "P3\n" << m_width << " " << m_height << "\n255\n";

	// Progress bar
	int progress_bar = 0;
	bool print = true;
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
				Ray ray = generateRay(camera, u, v);
				
				outColor += computeRay(ray, 0);
			}
			// Dividing the total of light received by all the sampled rays by the amount of samples
			outColor /= float(m_samples);
			
			if (print == true) {
				cout << " r : " << outColor.r() << " g : " << outColor.g() << " b : " << outColor.b() << endl;
			}
			
			outColor = vector3(sqrt(outColor[0]), sqrt(outColor[1]), sqrt(outColor[2]));

			if (print == true) {
				cout << " r : " << outColor.r() << " g : " << outColor.g() << " b : " << outColor.b() << endl;
			}

			print = false;

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


Ray RayTracer::generateRay(const Camera& camera, float u, float v) const
{
	return Ray(camera.position, camera.lower_left_corner + u * camera.horizontal + v * camera.vertical);
}


vector3 RayTracer::computeRay(const Ray& ray, int depth) const
{
	HitData hitdata;
	Ray bouncingRay;
	vector3 absorbedColor;

	if (m_world.isHit(ray, m_near_clip, m_far_clip, hitdata))
	{
		if (hitdata.shader_ptr == 0) {
			hitdata.shader_ptr = m_default_shader;
		}

		if (depth < m_max_depth && hitdata.shader_ptr->scatter(ray, hitdata, absorbedColor, bouncingRay)) {
			// Recursively sending rays each time the ray hits an object.
			return absorbedColor*computeRay(bouncingRay, depth + 1);
		}
		else {
			return vector3(0, 0, 0);
		}
		
	}
	else {
		// hit nothing -> skydome color
		return defaultColor(ray);
	}

}