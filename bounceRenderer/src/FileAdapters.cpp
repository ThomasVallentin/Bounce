#include "FileAdapters.h"


bool PPMAdapter::write(RayTracer& tracer) const
{
    // open file stream
    std::ofstream outFileStream(tracer.outpath());

    unsigned int width = tracer.camera().width();
    unsigned int height = tracer.camera().height();
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
