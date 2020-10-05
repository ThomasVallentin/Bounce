#include "core/RayTracer.hpp"

int intersectCount;

void printTimeInfo(const std::chrono::time_point<std::chrono::high_resolution_clock>& startTime, float percentage)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> currTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration duration = currTime - startTime;
    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()/1000.0;
    double remainingTime =  std::chrono::duration_cast<std::chrono::milliseconds>(duration / percentage * (100 - percentage)).count()/1000.0;
    std::cout << "Elapsed time : " << elapsedTime << "s | Remaining time : " << remainingTime << "s" << std::endl;
}


void RayTracer::initialize(Scene* sc)
{
    std::cout << "Initializing RayTracer..." << std::endl;

    scene = sc;

    unsigned int pixelsCount = m_camera.width() * m_camera.height();

    for (int i=0; i < pixelsCount; i++) {
        sampleBuffer.push_back(0);

        for (size_t j=0; j < 3; j++)
            pixelBuffer.emplace_back(0);
    }

    // Build the bbox of all the objects of the scene
    for (Shape* shape : scene->shapes)
        shape->buildBBox();

    // build the scene accelerator
    if (scene->accelerator != nullptr) {
        std::cout << "Building accelerator..." << std::endl;

        scene->accelerator->scene = scene;
        scene->accelerator->build();
    }

    m_sampler->initialize(this);
    intersectCount = 0;

    initialized = true;
}

void RayTracer::sampleCamera(const unsigned int &x, const unsigned int &y, Ray& ray) {
    // Sampling the camera using a very simple random sampling
    float urand = randomFlt();
    float vrand = randomFlt();
    float u = (float(x) + urand) / float(m_camera.width());
    float v = (float(y) + vrand) / float(m_camera.height());

    m_camera.generateRay(u, v, ray);
}

void RayTracer::render(Scene* sc) {
    initialize(sc);
    trace();
}

void RayTracer::trace()
{
    std::cout << "Tracing scene composed of " << scene->shapes.size() << " shapes..." << std::endl;

    // Init timer variables
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

	for (size_t thr=0 ; thr < threadCount() ; thr++) {
        threadPool.addJob(std::bind(&RayTracer::threadedTrace, this));
    }

	tileCount = threadPool.jobs.size();
    std::cout << "Rendering on " << threadPool.threadCount << " threads." << std::endl;

    threadPool.start();
	threadPool.join();

	std::cout << "Done ! Elapsed time : " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count()/1000.0 << "s" << std::endl;
    std::cout << "Ray-triangle intersections : " << intersectCount << std::endl;

//    for (auto &v : sampleBuffer)
//        std::cout << v << std::endl;

    std::vector<float> sampleMap;
    sampleMap.resize(camera().width() * camera().height()*3);
    for (size_t i=0; i < camera().width() * camera().height(); i++) {
        sampleMap[i*3] = sampleBuffer[i] / float(maxSamples());
        sampleMap[i*3 + 1] = sampleBuffer[i] / float(maxSamples());
        sampleMap[i*3 + 2] = sampleBuffer[i] / float(maxSamples());
    }
    writeImage();
//    adapter->write(m_outpath, camera().width(), camera().height(), sampleMap.data());
}

using namespace std::chrono_literals;

bool RayTracer::threadedTrace() {
    Color renderedColor;
    unsigned int x, y;
    Ray ray;

    // -- Main Render Loop --
    while (m_sampler->sampleRay(x, y, ray)) {

        // Computing & storing the light received by the ray
        renderedColor = computeIllumination(ray);
        {
            std::unique_lock<std::mutex> lock(writingPixelsMutex);
            mergeColorToPixel(x, y, renderedColor);
        }
    }

    return true;
}

Color RayTracer::computeIllumination(const Ray& ray, int depth) const
{
    if (depth > m_max_depth)
        return Color::Black();

    HitData hitdata;
    Color outColor = Color::Black();
    bool hasHit = scene->intersect(ray, nearClip, farClip, hitdata);

	if (!hasHit) {
        // hit nothing -> get color at infinity (EnvLights, SkyLights, etc...)
        for (auto light : scene->lights) {
            outColor += light->getInfiniteIllumination(ray);
        }
        return outColor;
    }

	// Compute bsdf properties at hit point
	hitdata.computeScattering();

    if (hitdata.bsdf == nullptr) {
        return Color::Black();
    }

    // Sample direct lighting
    Ray toLight;
    for (auto light : scene->lights) {
        toLight = light->getIllumination()
    }

    float pdf(0);
    Vector3 wi, wo(hitdata.wo);
//    std::cout << "wo " << wo << std::endl;
    Color f = hitdata.bsdf->sample(wo, wi, pdf);
//    std::cout << "f " << f << std::endl;
//    std::cout << "pdf " << pdf << std::endl;

    if (f.isBlack() || pdf == 0) {
        return Color::Black();
    }

    outColor += f * std::abs(dot(wi, hitdata.normal)) / pdf * computeIllumination(hitdata.generateRay(wi), depth + 1);

    return outColor;
}


void RayTracer::mergeColorToPixel(const unsigned int &x, const unsigned int &y, Color &color) {
    unsigned int sampleIndex = y * m_camera.width() + x;
    unsigned int colorIndex = sampleIndex * 3;
    unsigned int currentSample = sampleBuffer[sampleIndex];

    pixelBuffer[colorIndex]     = (pixelBuffer[colorIndex] * float(currentSample) + color.r) / float(currentSample + 1);
    pixelBuffer[colorIndex + 1] = (pixelBuffer[colorIndex + 1] * float(currentSample) + color.g) / float(currentSample + 1);
    pixelBuffer[colorIndex + 2] = (pixelBuffer[colorIndex + 2] * float(currentSample) + color.b) / float(currentSample + 1);

    m_sampler->update(x, y, color);

    sampleBuffer[sampleIndex]++;
}

//Color RayTracer::computeReflection(const Ray &ray, HitData &hitdata, const int depth) const {
//    Ray outRay;
//    Color absorbance;
//    if(hitdata.shader->sampleReflection(ray, hitdata, outRay, absorbance)) {
//        return absorbance * computeIllumination(outRay, depth + 1);
//    }
//    return Color::Black();
//}
//
//Color RayTracer::computeTransmission(const Ray &ray, HitData &hitdata, const int depth) const {
//    Ray outRay;
//    Color absorbance;
//    if(hitdata.shader->sampleTransmission(ray, hitdata, outRay, absorbance)) {
//        return absorbance * computeIllumination(outRay, depth + 1);
//    }
//    return Color::Black();
//}

bool RayTracer::writeImage() const {
    if (adapter == nullptr)
        return false;

    adapter->write(m_outpath, m_camera.width(), m_camera.height(), pixelBuffer.data());
    return true;
}


