//
// Created by Thomas Vallentin on 15/11/2020.
//

#ifndef BOUNCE_ARRAY2D_HPP
#define BOUNCE_ARRAY2D_HPP


template <typename T>
class Array2d {
public:
    Array2d(const unsigned int &width, const unsigned int &height) :
            width(width), height(height), length(height*width*channels), data(new T[length]) {}

    Array2d(const unsigned int &width, const unsigned int &height, T* input_data) :
            width(width), height(height), length(height*width), data(input_data) {
        for (size_t i=0 ; i < length ; i++ )
            data[i] = input_data[i];
    }

    T at(const unsigned int& x, const unsigned int &y) const { return data[(y * width + x)]; }
    T& operator[](const unsigned int&i) const { return data[i]; }
    T& operator[](const unsigned int&i) { return data[i]; }



    const unsigned int width, height, length;
private:
    T *data;
};


#endif //BOUNCE_ARRAY2D_HPP
