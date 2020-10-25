//
// Created by Thomas Vallentin on 19/10/2020.
//

#ifndef BOUNCE_INCANDESCENT_HPP
#define BOUNCE_INCANDESCENT_HPP

#include "core/Light.hpp"
#include "core/Material.hpp"
#include "core/BSDF.hpp"

class IncandescentMaterial : public Material {
public:
    explicit IncandescentMaterial(AreaLight *light) : light(light) {}

    void computeScattering(HitData &hitdata) const override {
        hitdata.bsdf = new BSDF(hitdata);
    }

    virtual Color getEmission(HitData &hitdata, const Vector3 &w) const {
        return light->lightEmitted(hitdata, w);
    };

private:
    const AreaLight *light;
};


#endif //BOUNCE_INCANDESCENT_HPP
