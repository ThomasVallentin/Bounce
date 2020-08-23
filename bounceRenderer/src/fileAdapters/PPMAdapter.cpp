//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "fileAdapters/PPMAdapter.hpp"


bool PPMAdapter::write(const std::string& outpath, const unsigned int& width, const unsigned int& height, const float* pixels) const
{
    // open file stream
    std::ofstream outFileStream(outpath);

    // Write ppm format data
    outFileStream << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned int pixelIndex = (y * width + x) * 3;
            Color color(pixels[pixelIndex], pixels[pixelIndex + 1],
                        pixels[pixelIndex + 2]);

            color = applyGamma(color, 2.2);
            color = colorfToColor8(color);

            outFileStream << int(color.r) << " " << int(color.g) << " " << int(color.b) << "\n";
        }
    }

    return true;
}