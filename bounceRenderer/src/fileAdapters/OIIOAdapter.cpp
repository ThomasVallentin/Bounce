//
// Created by Thomas Vallentin on 02/12/2020.
//

#include "adapters/OIIOAdapter.hpp"

bool OIIOAdapter::write(const std::string &outpath, const unsigned int &width, const unsigned int &height,
                        const float *pixels) const {
    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create (outpath);
    if (!out)
        return false;

    size_t pixelCount = width*height*3;

    float *toWritePixels = new float[pixelCount];
    for (size_t i=0; i < (pixelCount) ; i++)
        toWritePixels[i] = applyGamma(pixels[i], 2.2);

    OIIO::ImageSpec spec ((int)width, (int)height, 3, OIIO::TypeDesc::FLOAT);
    out->open (outpath, spec);
    out->write_image (OIIO::TypeDesc::FLOAT, toWritePixels);
    out->close ();

    return true;
}
