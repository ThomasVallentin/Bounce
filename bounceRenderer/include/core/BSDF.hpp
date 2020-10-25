//
// Created by Thomas Vallentin on 20/09/2020.
//

#ifndef BOUNCE_BSDF_HPP
#define BOUNCE_BSDF_HPP
#define MAX_BXDF 12

#include "core/Vector3.hpp"
#include "core/BxDF.hpp"
#include "core/Ray.h"
#include "core/Material.hpp"


class BSDF {
public:
    explicit BSDF(const HitData &data) : N(data.normal), tan1(data.tan1), tan2(data.tan2) {}
    ~BSDF();

    virtual Color sample(Vector3 &woWorld, Vector3 &wiWorld, float &pdf) const;
    virtual Color evaluate(Vector3 &woWorld, Vector3 &wiWorld) const;
    virtual float computePdf(Vector3 &woWorld, Vector3 &wiWorld) const;

    void addBxDF(BxDF *bxdf) { bxdfs[bxdfCount++] = bxdf; }
    Vector3 worldToLocal(const Vector3 &vec) const { return ::worldToLocal(vec, tan1, tan2, N); }
    Vector3 localToWorld(const Vector3 &vec) const { return ::localToWorld(vec, tan1, tan2, N); }

private:
    size_t bxdfCount = 0;
    BxDF *bxdfs[8]{};

    const Vector3 N, tan1, tan2;
};


#endif //BOUNCE_BSDF_HPP
