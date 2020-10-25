//
// Created by Thomas Vallentin on 20/09/2020.
//

#include "core/BSDF.hpp"

HitData::~HitData() {
    delete bsdf;
}

BSDF::~BSDF() {
    for (int i=0 ; i< bxdfCount ; i++)
        delete bxdfs[i];
}

Color BSDF::sample(Vector3 &woWorld, Vector3 &wiWorld, float &pdf) const {
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
        pdf /= bxdfCount;
    }

    return outColor;
}

Color BSDF::evaluate(Vector3 &woWorld, Vector3 &wiWorld) const {
    if (bxdfCount == 0) {
        return Color::Black();
    }

    Vector3 wo(worldToLocal(woWorld)), wi(worldToLocal(wiWorld));
    if (wo.z == 0)
        return 0;

    Color outColor = Color::Black();

    for (size_t i = 0; i < bxdfCount; i++)
        outColor += bxdfs[i]->evaluate(wo, wi);

    return outColor;
}

float BSDF::computePdf(Vector3 &woWorld, Vector3 &wiWorld) const {
    if (bxdfCount == 0) {
        return 0;
    }

    Vector3 wo(worldToLocal(woWorld)), wi(worldToLocal(wiWorld));
    if (wo.z == 0)
        return 0;

    float pdf = 0;

    if (bxdfCount > 0) {
        for (size_t i = 0; i < bxdfCount; i++)
            pdf += bxdfs[i]->computePdf(wo, wi);

        pdf /= bxdfCount;
    }

    return pdf;
}
