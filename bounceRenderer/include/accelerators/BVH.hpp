//
// Created by Thomas Vallentin on 26/08/2020.
//

#ifndef BOUNCE_BVH_HPP
#define BOUNCE_BVH_HPP


#include "core/Accelerator.hpp"
#include "core/Scene.hpp"


class BVH : public Accelerator {
public:
    BVH() : Accelerator() {}
    explicit BVH(Scene* scene) :
            Accelerator(scene), subnode1(nullptr), subnode2(nullptr) {}
    bool build() override;
    bool intersect(const Ray &ray, float tmin, float tmax, HitData &data) const override;
    bool intersectAny(const Ray &ray, float tmin, float tmax, HitData &tempdata) const override;

    void buildSubnodes(const unsigned int& iStart, const unsigned int& iEnd);
    void buildBBox(const unsigned int& i0, const unsigned int& i1);

    BoundingBox buildBarycentricBBox(const unsigned int& i0, const unsigned int& i1);
    BoundingBox bbox;
    unsigned int iStart, iEnd;

    BVH *subnode1, *subnode2;
};



#endif //BOUNCE_BVH_HPP
