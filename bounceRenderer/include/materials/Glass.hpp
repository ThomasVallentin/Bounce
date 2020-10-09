//
// Created by Thomas Vallentin on 06/10/2020.
//

#ifndef BOUNCE_GLASS_HPP
#define BOUNCE_GLASS_HPP

#include "core/Material.hpp"
#include "core/BSDF.hpp"

class GlassMaterial : public Material {
public:
    GlassMaterial(const Color &specularColor, const Color &transmissionColor, const float &ior) :
            specularColor(specularColor), transmissionColor(transmissionColor), ior(ior) {}

    void computeScattering(HitData &hitdata) const override {
        hitdata.bsdf = new BSDF(hitdata);

        if (!transmissionColor.isBlack()) {
            hitdata.bsdf->addBxDF(new SpecularTransmission(transmissionColor, ior));
        }

        if (!specularColor.isBlack()) {
            hitdata.bsdf->addBxDF(new SpecularReflection(specularColor, ior));
        }
    }

private:
    const Color specularColor;
    const Color transmissionColor;
    const float ior;
};


#endif //BOUNCE_GLASS_HPP
