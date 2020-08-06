#include "FileAdapters.h"


bool PPMAdapter::write(RayTracer& tracer) const
    {

    // opening file stream
    std::ofstream outputStream(tracer.outpath());

    float width = tracer.camera().width();
    float height = tracer.camera().height();
    // Write ppm format data
    outputStream << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0; x < width; x++) {
            unsigned int pixelIndex = (y * width + x) * 3;
            vector3 color(tracer.pixels()[pixelIndex], tracer.pixels()[pixelIndex + 1], tracer.pixels()[pixelIndex + 2]);
            color = applyGamma(color, 2.2);

            // 0.0 to 1.0 -> 0 to 255
            color = unitToColor(color);

            outputStream << int(color.r()) << " " << int(color.g()) << " " << int(color.b()) << "\n";
        }
    }

    return true;
}

