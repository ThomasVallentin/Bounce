//
// Created by Thomas Vallentin on 01/09/2020.
//

#ifndef BOUNCE_SAMPLER_HPP
#define BOUNCE_SAMPLER_HPP


struct Tile;
class RayTracer;
class Ray;
class Color;

class Sampler {
public:
    Sampler() = default;;

    virtual void initialize(RayTracer* tracer) = 0;
    virtual bool sampleRay(unsigned int &u, unsigned int &v, Ray &ray) = 0;
    virtual void sampleCamera(Ray &ray) = 0;
    virtual void update(const unsigned int &u, const unsigned int &v, const Color& color) = 0;

};




#endif //BOUNCE_SAMPLER_HPP
