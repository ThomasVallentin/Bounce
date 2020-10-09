//
// Created by Thomas Vallentin on 01/10/2020.
//

#ifndef BOUNCE_PLASTIC_HPP
#define BOUNCE_PLASTIC_HPP

#include "core/Material.hpp"
#include "core/BSDF.hpp"

class PlasticMaterial : public Material {
public:
    PlasticMaterial(const Color &albedo, const Color &specularColor) :
            albedo(albedo), specularColor(specularColor) {}

    void computeScattering(HitData &hitdata) const override {
        hitdata.bsdf = new BSDF(hitdata);

        if (!specularColor.isBlack()) {
            hitdata.bsdf->addBxDF(new SpecularReflection(specularColor, 1.5));
        }

        if (!albedo.isBlack()) {
            hitdata.bsdf->addBxDF(new LambertianReflection(albedo));
        }
    }

private:
    const Color albedo;
    const Color specularColor;
};


#endif //BOUNCE_PLASTIC_HPP
