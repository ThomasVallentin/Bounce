#include "FileAdapters.h"

vector3 unitToColor(const vector3& vec);
vector3 applyGamma(const vector3& color, float gamma);

bool PPMAdapter::write(const std::string& path,
                       const unsigned int& width,
                       const unsigned int& height,
                       std::vector<float>& pixels) const
    {

    // opening file stream
    std::ofstream outputStream(path);

    // Write ppm format data
    outputStream << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0; x < width; x++) {
            unsigned int pixelIndex = (y*width + x)*3;
            vector3 color(pixels[pixelIndex], pixels[pixelIndex + 1], pixels[pixelIndex + 2]);
            color = applyGamma(color, 2.2);

            // 0.0 to 1.0 -> 0 to 255
            color = unitToColor(color);

            outputStream << int(color.r()) << " " << int(color.g()) << " " << int(color.b()) << "\n";
        }
    }

    return true;
}

