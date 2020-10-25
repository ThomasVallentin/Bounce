//
// Created by Thomas Vallentin on 19/10/2020.
//

#ifndef BOUNCE_DISC_HPP
#define BOUNCE_DISC_HPP

#include "core/Shape.hpp"
#include "core/mathUtils.h"


class Disc : public Shape {
public:
    Disc() : radius(1.0f) {}
    Disc(const float &radius) : radius(radius) {}
    Disc(const Transform *transform, const float &radius) : Shape(transform, nullptr), radius(radius) {}
    Disc(const Transform *transform, const float &radius, Material *material) : Shape(transform, material), radius(radius) {}

    bool intersect(const Ray &ray, float tmin, float tmax, HitData &hitdata) const override;
    virtual void buildBBox() override;
    virtual Point3 barycenter() const override;

    virtual HitData sample(float &pdf) const;

    float area() const override;

private:
    float radius{};
};


#endif //BOUNCE_DISC_HPP
