#include "RayTracer.h"


vector3 unitToColor(const vector3& vec) {
	return vector3(vec.r() * 255.9f, vec.g() * 255.9f, vec.b() * 255.9f);
}

vector3 applyGamma(const vector3& color, float gamma) {
	float factor = 1 / gamma;

	return vector3(pow(color[0], factor), pow(color[1], factor), pow(color[2], factor));
}

void printTimeInfo(const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime, float percentage)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> currTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration duration = currTime - startTime;
    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()/1000.0;
    double remainingTime =  std::chrono::duration_cast<std::chrono::milliseconds>(duration / percentage * (100 - percentage)).count()/1000.0;
    std::cout << "Elapsed time : " << elapsedTime << "s | Time remaining : " << remainingTime << "s" << std::endl;
}


bool RayTracer::initialize()
{
    std::cout << "Initializing RayTracer..." << std::endl;

    int pixelsFullLength = m_width * m_height * 3;

    m_pixels.resize(pixelsFullLength);
    for (int i=0; i < pixelsFullLength; i++)
    {
        m_pixels[i] = 0;
    }
}

bool RayTracer::trace(const Camera& camera)
{
    std::cout << "Tracing scene composed of " << m_world.list().size() << " hitables..." << std::endl;

	// Progress bar
	float progress(0);

	// Init timer variables
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    int colorIndex;
    vector3 storedColor, renderedColor;
    for (int s = 0; s < m_samples; s++)
    {
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                colorIndex = (y * m_width + x) * 3;
                storedColor[0] = m_pixels[colorIndex];
                storedColor[1] = m_pixels[colorIndex + 1];
                storedColor[2] = m_pixels[colorIndex + 2];

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

                m_pixels[colorIndex] = storedColor.r();
                m_pixels[colorIndex + 1] = storedColor.g();
                m_pixels[colorIndex + 2] = storedColor.b();
            }
        }
        progress = float(s+1) / float(m_samples) * 100;
        std::cout << "Rendering " << std::setprecision(4) << progress << "%... ";

        // Print timer
        printTimeInfo(startTime, progress);
    }

    std::cout << "Done !" << std::endl;

    PPMAdapter adapter;
    adapter.write(*this);

	return true;
}


Ray RayTracer::generateRay(const Camera& camera, float u, float v) const
{
	return Ray(camera.position, camera.top_left_corner + u * camera.horizontal - v * camera.vertical);
}


vector3 RayTracer::computeRay(const Ray& ray, int depth) const
{
	HitData hitdata;

	if (m_world.intersect(ray, m_near_clip, m_far_clip, hitdata))
	{
		if (hitdata.shader_ptr == 0) {
			hitdata.shader_ptr = m_default_shader;
		}

        std::vector<Ray> outRays;
        std::vector<vector3> absorbedColors;
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
		return vector3(.8, .8, 1);
	}

}