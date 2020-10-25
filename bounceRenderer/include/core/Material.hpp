//
// Created by Thomas Vallentin on 01/10/2020.
//

#ifndef BOUNCE_MATERIAL_HPP
#define BOUNCE_MATERIAL_HPP

#include "core/Vector3.hpp"
#include "core/Color.hpp"

class HitData;


class Material {
public:
    Material() = default;
    virtual void computeScattering(HitData &hitdata) const = 0;
    virtual Color getEmission(HitData &hitdata, const Vector3 &w) const { return Color::Black(); };
};


#endif //BOUNCE_MATERIAL_HPP
