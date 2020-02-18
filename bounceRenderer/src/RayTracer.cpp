#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

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

bool RayTracer::initialize()
{
    cout << "Initializing RayTracer..." << endl;
    int pixelsFullLength = m_width * m_height * 3;
    m_result.resize(pixelsFullLength);
    for (int i=0; i < pixelsFullLength; i++)
    {
        m_result[i] = 0;
    }
}

bool RayTracer::trace(const Camera& camera)
{
	cout << "Tracing scene composed of " << m_world.list().size() << " hitables..." << endl;

	// opening file stream
	ofstream outputStream(m_outpath);

	// Progress bar
	int progress_bar = 0;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			vector3 rawColor(0, 0, 0);

			for (int s = 0; s < m_samples; s++) {
				// cout << randomFlt() << endl;
				float urand = randomFlt();
				float vrand = randomFlt();
				float u = float(x + urand) / m_width;
				float v = float(y + vrand) / m_height;
				// cout << u << " " << v << endl;
				Ray ray = generateRay(camera, u, v);
				rawColor += computeRay(ray, 0);
			}
			// Dividing the total of light received by all the sampled rays by the amount of samples
			rawColor /= float(m_samples);
			
			vector3 gammaColor = applyGamma(rawColor, 2.2);

			// 0.0 to 1.0 -> 0 to 255
			gammaColor = unitToColor(gammaColor);
			
            m_result[(y*m_width+ x) * 3] = (uint8_t(gammaColor.r()));
            m_result[(y*m_width+ x) * 3 + 1] = (uint8_t(gammaColor.g()));
            m_result[(y*m_width+ x) * 3 + 2] = (uint8_t(gammaColor.b()));
		}

		if (int((y / float(m_height)) *100) > progress_bar) {
			cout << "Rendering " << progress_bar << "%..." << endl;
			progress_bar += 5;
		}
	}

    cout << "Done !" << endl;

	return true;
}


Ray RayTracer::generateRay(const Camera& camera, float u, float v) const
{
	return Ray(camera.position, camera.top_left_corner + u * camera.horizontal - v * camera.vertical);
}


vector3 RayTracer::computeRay(const Ray& ray, int depth) const
{
	HitData hitdata;

	if (m_world.isHit(ray, m_near_clip, m_far_clip, hitdata))
	{
		if (hitdata.shader_ptr == 0) {
			hitdata.shader_ptr = m_default_shader;
		}

		vector<Ray> outRays;
		vector<vector3> absorbedColors;
		vector3 outColor(0, 0, 0);
		if (depth < m_max_depth && hitdata.shader_ptr->scatter(ray, hitdata, absorbedColors, outRays)) {
			for (int i = 0; i < outRays.size(); i++) {
				outColor += absorbedColors[i] * computeRay(outRays[i], depth + 1);
			}
			return outColor;
		}
		else {
			return vector3(0, 0, 0);
		}

	}
	else {
		// hit nothing -> skydome color
		//return defaultColor(ray);
		return vector3(.8, .8, 1);
	}

}