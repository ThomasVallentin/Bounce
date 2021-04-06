//
// Created by Thomas Vallentin on 15/11/2020.
//

#include "core/Texture.hpp"


template <typename T>
std::map<std::string, std::unique_ptr<Array2d<T>>> ImageTexture<T>::textureCache;


template<typename T>
Array2d<T> *ImageTexture<T>::getTexture(const std::string &filepath) {
    // Search for the texture in the cache
    if (textureCache.find(filepath) == textureCache.end()) {
        int width, height;
        Color *data = readImage(filepath, width, height);

        if (!data) {
            data = new Color[1]{0.5};
            width = 1;
            height = 1;
        }

        T *pixels = new T[width * height];
        for (int i = 0 ; i < width * height ; i++) {
            pixels[i] = T(data[i]);
        }
        delete data;

        textureCache[filepath] = std::unique_ptr<Array2d<T>>(new Array2d(width, height, pixels));
    }

    return textureCache[filepath].get();
}


template<typename T>
T ImageTexture<T>::sample(const HitData &hitdata) const {
    return T();
}

template<typename T>
T ImageTexture<T>::sample(const float &u, const float &v) const {
    std::cout << map << std::endl;
    return map->at(u*(map->width-1), v*(map->height-1));
}


Color* readImage(const std::string &filepath, int &width, int &height) {
    std::unique_ptr<OIIO::ImageInput> image = OIIO::ImageInput::open(filepath);
    if (!image){
        std::cout << "image " << image << std::endl;
        return nullptr;}

    const OIIO::ImageSpec &spec = image->spec();

    // Set image resolution from spec
    width = spec.width;
    height = spec.height;

    // Force channel count to be 1 or 3 to avoid problematics
    int channels = std::min(spec.nchannels, 3);
    if (channels < 3)
        channels = 1;

    std::unique_ptr<float[]> pix(new float[width * height * channels]);
    bool succeeded = image->read_image(0, channels, OIIO::TypeDesc::FLOAT, pix.get());

    if (!succeeded){
        std::cout << "succeeded " << succeeded << std::endl;
        return nullptr;}

    Color *result(new Color[width * height]);
    if (channels == 1)
        for (int i=0 ; i<width * height ; i++)
            result[i] = Color(pix[i]);
    else
        for (int i=0 ; i < width * height ; i++)
            result[i] = Color(pix[i * 3], pix[i * 3 + 1], pix[i * 3 + 2]);

    return result;
}


// Declare common texture types
template class ImageTexture<float>;
template class ImageTexture<Color>;
