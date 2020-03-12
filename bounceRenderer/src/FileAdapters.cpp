#include "FileAdapters.h"


bool PPMAdapter::write(RayTracer& tracer) const
    {

    // opening file stream
    std::ofstream outputStream(tracer.outpath());

    // Write ppm format data
    outputStream << "P3\n" << tracer.width() << " " << tracer.height() << "\n255\n";

    for (int y = 0 ; y < tracer.height() ; y++)
    {
        for (int x = 0; x < tracer.width(); x++) {
            unsigned int pixelIndex = (y*tracer.width() + x)*3;
            vector3 color(tracer.pixels()[pixelIndex], tracer.pixels()[pixelIndex + 1], tracer.pixels()[pixelIndex + 2]);
            color = applyGamma(color, 2.2);

            // 0.0 to 1.0 -> 0 to 255
            color = unitToColor(color);

            outputStream << int(color.r()) << " " << int(color.g()) << " " << int(color.b()) << "\n";
        }
    }

    return true;
}

