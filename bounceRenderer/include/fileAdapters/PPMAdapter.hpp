//
// Created by Thomas Vallentin on 23/08/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_PPMADAPTER_HPP
#define BOUNCE_PPMADAPTER_HPP


#include "FileAdapters.hpp"


class PPMAdapter : public FileAdapter
{
public:
    PPMAdapter() : FileAdapter() {}
    bool write(const std::string& outpath, const unsigned int& width, const unsigned int& height, const float* pixels) const override;

};


#endif //BOUNCE_PPMADAPTER_HPP
