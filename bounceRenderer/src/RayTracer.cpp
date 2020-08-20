#include "RayTracer.h"

void printTimeInfo(const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime, float percentage)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> currTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration duration = currTime - startTime;
    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()/1000.0;
    double remainingTime =  std::chrono::duration_cast<std::chrono::milliseconds>(duration / percentage * (100 - percentage)).count()/1000.0;
    std::cout << "Elapsed time : " << elapsedTime << "s | Remaining time : " << remainingTime << "s" << std::endl;
}


bool RayTracer::initialize()
{
    std::cout << "Initializing RayTracer..." << std::endl;

    unsigned int pixelsFullLength = m_camera.width() * m_camera.height() * 3;

    m_pixels.resize(pixelsFullLength);
    for (int i=0; i < pixelsFullLength; i++)
    {
        m_pixels[i] = 0;
    }
    // TODO(c++ course): insert may be a better way than looping:
    // m_pixels.clear();
    // m_pixels.insert(m_pixels.begin(), pixelsFullLength, 0);
    return true;
}

void RayTracer::sampleCamera(unsigned int x, unsigned int y, Ray &ray) {
    // Sampling the camera using a very simple random sampling
    float urand = randomFlt();
    float vrand = randomFlt();
    float u = (float(x) + urand) / float(m_camera.width());
    float v = (float(y) + vrand) / float(m_camera.height());

    m_camera.generateRay(u, v, ray);
}

bool RayTracer::trace(Scene* sc)
{
    scene = sc;

    std::cout << "Tracing scene composed of " << scene->shapes().size() << " shapes..." << std::endl;

	// Progress bar
	float progress(0);

	// Init timer variables
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    unsigned int colorIndex;
    Color storedColor, renderedColor;
    Ray ray;
    for (int s = 0; s < m_samples; s++)
    {
        for (unsigned int y = 0; y < m_camera.height(); y++)
        {
            for (unsigned int x = 0; x < m_camera.width(); x++)
            {
                // Sample the camera to the (x, y) pixel and fill the Ray with the content
                sampleCamera(x, y, ray);

                // Adding the new sample to the existing render
                renderedColor = computeRay(ray, 0);
                // std::cout << "    " << renderedColor << std::endl;

                colorIndex = (y * m_camera.width() + x) * 3;
                storedColor.r = m_pixels[colorIndex];
                storedColor.g = m_pixels[colorIndex + 1];
                storedColor.b = m_pixels[colorIndex + 2];

                storedColor = (storedColor * float(s) + renderedColor) / float(s + 1);
                //  std::cout << " after: " << storedColor << std::endl;

                m_pixels[colorIndex] = storedColor.r;
                m_pixels[colorIndex + 1] = storedColor.g;
                m_pixels[colorIndex + 2] = storedColor.b;
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


Color RayTracer::computeRay(const Ray& ray, int depth) const
{
	HitData hitdata;

	if (scene->intersect(ray, m_near_clip, m_far_clip, hitdata))
	{
		if (hitdata.shader_ptr == nullptr) {
			hitdata.shader_ptr = m_default_shader;
		}

        std::vector<Ray> outRays;
        std::vector<Color> absorbedColors;
		Color outColor;
		if (depth < m_max_depth && hitdata.shader_ptr->scatter(ray, hitdata, absorbedColors, outRays)) {
			for (int i = 0; i < outRays.size(); i++) {
				outColor += absorbedColors[i] * computeRay(outRays[i], depth + 1);
			}
			return outColor;
		}
		else {
			return Color(0.0f, 0.0f, 0.0f);
		}

	}
	else {
		// hit nothing -> skydome color
		return Color(0.8f, 0.8f, 1.0f);
	}

}


