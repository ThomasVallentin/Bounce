//
// Created by Thomas Vallentin on 15/11/2020.
//

#ifndef BOUNCE_TEXTURE_HPP
#define BOUNCE_TEXTURE_HPP

#include <OpenImageIO/imageio.h>

#include "core/Ray.h"
#include "core/Array2d.hpp"

#include <map>
#include <string>

template<typename T>
class Texture {
public:
    Texture() = default;

    virtual T sample(const HitData &hitdata) const { return T(); };
};


template<typename T>
class ConstantTexture : public Texture<T> {
public:
    explicit ConstantTexture(const T &value) : value(value) {}

    T sample(const HitData &hitdata) override { return value; }

private:
    const T value;
};


template<typename T>
class ImageTexture : public Texture<T> {
public:
    explicit ImageTexture(const std::string &filepath) {
        map = getTexture(filepath);
    }

    static Array2d<T> *getTexture(const std::string &filepath);

    T sample(const HitData &hitdata) const override;
    T sample(const float &u, const float &v) const;

private:
    static std::map<std::string, std::unique_ptr<Array2d<T>>> textureCache;
    Array2d<T> *map;
};



#endif //BOUNCE_TEXTURE_HPP
