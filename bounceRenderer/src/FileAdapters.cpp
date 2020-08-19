#include "FileAdapters.h"


bool PPMAdapter::write(RayTracer& tracer) const
{
    // opening file stream
    std::ofstream outFileStream(tracer.outpath());

    float width = tracer.camera().width();
    float height = tracer.camera().height();
    // Write ppm format data
    outFileStream << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned int pixelIndex = (y * width + x) * 3;
            Color color(tracer.pixels()[pixelIndex], tracer.pixels()[pixelIndex + 1],
                        tracer.pixels()[pixelIndex + 2]);

            color = applyGamma(color, 2.2);
            color = colorfToColor8(color);

            outFileStream << int(color.r) << " " << int(color.g) << " " << int(color.b) << "\n";
        }
    }

    return true;
}
