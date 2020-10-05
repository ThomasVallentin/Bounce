//
// Created by Thomas Vallentin on 03/10/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCE_LAMBERT_HPP
#define BOUNCE_LAMBERT_HPP

#include "core/Material.hpp"
#include "core/BSDF.hpp"

class LambertMaterial : public Material {
public:
    explicit LambertMaterial(const Color &albedo) : albedo(albedo) {}

    void computeScattering(HitData &hitdata) const override {
        hitdata.bsdf = new BSDF(hitdata);

        if (!albedo.isBlack()) {
            hitdata.bsdf->addBxDF(new LambertianBRDF(albedo));
        }
    }

private:
    const Color albedo;
};


#endif //BOUNCE_LAMBERT_HPP
