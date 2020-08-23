#include "RayTracer.hpp"

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

void RayTracer::sampleCamera(const unsigned int &x, const unsigned int &y, Ray& ray) {
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

    std::cout << "Tracing scene composed of " << scene->shapes.size() << " shapes..." << std::endl;

	// Progress bar
	float progress(0);

	// Init timer variables
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    // -- Main Render Loop --
    Color renderedColor;
    Ray ray;
    for (unsigned int s = 0; s < m_samples; s++)
    {
        for (unsigned int y = 0; y < m_camera.height(); y++)
        {
            for (unsigned int x = 0; x < m_camera.width(); x++)
            {
                // Sample the camera to the (x, y) pixel & fill the ray
                sampleCamera(x, y, ray);

                // Adding the new sample to the existing render
                renderedColor = computeIllumination(ray);

                // Merge the rendered color with the already rendered pixel (merge colors based on sample)
                mergeColorToPixel(x, y, s, renderedColor);
            }
        }
        progress = float(s+1) / float(m_samples) * 100;
        std::cout << "Rendering " << std::setprecision(4) << progress << "%... ";

        // Print elapsed & remaining time
        printTimeInfo(startTime, progress);
    }

    std::cout << "Done !" << std::endl;

    PPMAdapter adapter;
    adapter.write(*this);

	return true;
}


Color RayTracer::computeIllumination(const Ray& ray, int depth) const
{
    if (depth > m_max_depth)
        return Color::Black();

    HitData hitdata;
    Color outColor = Color::Black();

	if (!scene->intersect(ray, m_near_clip, m_far_clip, hitdata)) {
        // hit nothing -> get color at infinity (EnvLights, SkyLights, etc...)
        for (auto light : scene->lights) {
            outColor += light->getInfiniteIllumination(ray);
        }
        return outColor;
    }

	// Ensure hit object has a shader
    if (hitdata.shader == nullptr) {
        hitdata.shader = m_default_shader;
    }

    // Sample light diffusion
    Ray outRay;
    Color absorbance;
    if(hitdata.shader->sampleDiffusion(ray, hitdata, outRay, absorbance)) {
        outColor += absorbance * computeIllumination(outRay, depth + 1);
    }

    // Sample direct lighting
    for (auto light : scene->lights) {
        outColor += absorbance * light->getIllumination(hitdata, scene);
    }

    outColor += computeReflection(ray, hitdata, depth);
    outColor += computeTransmission(ray, hitdata, depth);

    return outColor;
}

void RayTracer::mergeColorToPixel(const unsigned int &x, const unsigned int &y, unsigned int &currentSample, Color &color) {
    unsigned int colorIndex = (y * m_camera.width() + x) * 3;

    m_pixels[colorIndex]     = (m_pixels[colorIndex]     * float(currentSample) + color.r)     / float(currentSample + 1);
    m_pixels[colorIndex + 1] = (m_pixels[colorIndex + 1] * float(currentSample) + color.g) / float(currentSample + 1);
    m_pixels[colorIndex + 2] = (m_pixels[colorIndex + 2] * float(currentSample) + color.b) / float(currentSample + 1);
}


Color RayTracer::computeReflection(const Ray &ray, HitData &hitdata, const int depth) const {
    Ray outRay;
    Color absorbance;
    if(hitdata.shader->sampleReflection(ray, hitdata, outRay, absorbance)) {
        return absorbance * computeIllumination(outRay, depth + 1);
    }
    return Color::Black();
}


Color RayTracer::computeTransmission(const Ray &ray, HitData &hitdata, const int depth) const {
    Ray outRay;
    Color absorbance;
    if(hitdata.shader->sampleTransmission(ray, hitdata, outRay, absorbance)) {
        return absorbance * computeIllumination(outRay, depth + 1);
    }
    return Color::Black();
}


