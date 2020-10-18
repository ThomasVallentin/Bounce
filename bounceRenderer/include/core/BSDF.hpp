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
    explicit BSDF(const HitData &data) :
            N(data.normal), tan1(data.tan1), tan2(data.tan2) {}
    ~BSDF() {
        for (int i=0 ; i< bxdfCount ; i++)
            delete bxdfs[i];
    }

    virtual Color sample(Vector3 &woWorld, Vector3 &wiWorld, float &pdf) const {
        if (bxdfCount == 0) {
            pdf = 0;
            return Color::Black();
        }

        float rand = uniform(engine);

        size_t BxDFIdx = std::min(size_t(std::floor(rand * bxdfCount)), bxdfCount - 1);
        BxDF *bxdf = bxdfs[BxDFIdx];

        // Initialize local wo, local wi & pdf
        Vector3 wi, wo = worldToLocal(woWorld);
        if (wo.z == 0)
            return Color::Black();
        pdf = 0;

        // Sample picked BxDF
        Color outColor = bxdf->sample(wo, wi, pdf);

        // If there the returned sample has no probability, return black
        if (pdf == 0)
            return Color::Black();

        wiWorld = localToWorld(wi);

        if (!(bxdf->type & BxDFType::SPECULAR) && bxdfCount > 1) {
            for (size_t i = 0; i < bxdfCount; i++)
                if (i != BxDFIdx) {
                    pdf += bxdfs[i]->computePdf(wo, wi);
                    outColor += bxdfs[i]->evaluate(wo, wi);
                }
        }
        pdf /= bxdfCount;

        return outColor;
    }

    void addBxDF(BxDF *bxdf) {
        bxdfs[bxdfCount++] = bxdf;
    }

    Vector3 worldToLocal(const Vector3 &vec) const {
        return ::worldToLocal(vec, tan1, tan2, N);
    }
    Vector3 localToWorld(const Vector3 &vec) const {
        return ::localToWorld(vec, tan1, tan2, N);
    }

private:
    size_t bxdfCount = 0;
    BxDF *bxdfs[8]{};

    const Vector3 N, tan1, tan2;
};


#endif //BOUNCE_BSDF_HPP
