//
// Created by Thomas Vallentin on 02/12/2020.
//

#ifndef BOUNCE_OIIOADAPTER_HPP
#define BOUNCE_OIIOADAPTER_HPP

#include "core/FileAdapters.hpp"
#include "OpenImageIO/imageio.h"


class OIIOAdapter : public FileAdapter {
public:
    OIIOAdapter() = default;
    bool write(const std::string &outpath, const unsigned int &width, const unsigned int &height, const float *pixels) const override;
};


#endif //BOUNCE_OIIOADAPTER_HPP
