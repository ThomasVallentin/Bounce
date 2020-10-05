//
// Created by Thomas Vallentin on 01/10/2020.
//

#ifndef BOUNCE_MATERIAL_HPP
#define BOUNCE_MATERIAL_HPP

class HitData;


class Material {
public:
    Material() = default;
    virtual void computeScattering(HitData &hitdata) const = 0;
};


#endif //BOUNCE_MATERIAL_HPP
