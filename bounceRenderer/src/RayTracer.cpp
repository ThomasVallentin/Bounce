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

	// Progress bar
	int progress = 0;

    int colorIndex;
    vector3 storedColor, renderedColor;
    for (int s = 0; s < m_samples; s++)
    {
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                colorIndex = (y * m_width + x) * 3;
                storedColor[0] = m_result[colorIndex];
                storedColor[1] = m_result[colorIndex + 1];
                storedColor[2] = m_result[colorIndex + 2];

                float urand = randomFlt();
                float vrand = randomFlt();
                float u = float(x + urand) / m_width;
                float v = float(y + vrand) / m_height;

                Ray ray = generateRay(camera, u, v);

                // Adding the new sample to the existing render
                renderedColor = computeRay(ray, 0);
                // std::cout << "    " << renderedColor << std::endl;

                storedColor = (storedColor * float(s) + renderedColor) / float(s + 1);
                //  std::cout << " after: " << storedColor << std::endl;

                m_result[colorIndex] = storedColor.r();
                m_result[colorIndex + 1] = storedColor.g();
                m_result[colorIndex + 2] = storedColor.b();

                if (int((s / float(m_samples)) * 100) > progress) {
                    cout << "Rendering " << progress << "%..." << endl;
                    progress += 5;
                }
            }
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