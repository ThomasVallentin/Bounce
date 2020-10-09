 //
// Created by Thomas Vallentin on 23/09/2020.
//

#ifndef BOUNCE_BXDF_HPP
#define BOUNCE_BXDF_HPP

#include "mathUtils.h"
#include "Color.hpp"

inline float cosTheta(const Vector3 &w) { return w.z; }
inline float absCosTheta(const Vector3 &w) { return std::abs(w.z); }

enum BxDFType{
    REFLECTION = 1 << 0,
    TRANSMISSION = 1 << 1,
    SPECULAR = 1 << 2,
    SUBSURFACE = 1 << 3,
    ALL = REFLECTION | TRANSMISSION | SPECULAR | SUBSURFACE,
};

class BxDF {
public:
    BxDF(BxDFType t) : type(t) {}

    bool matchFlags(BxDFType t) const {
        return (type & t) == type;
    }

    virtual Color sample(Vector3 &wo, Vector3 &wi, float &pdf) const;
    virtual Color evaluate(Vector3 &wo, Vector3 &wi) const = 0;
    virtual float computePdf(Vector3 &wo, Vector3 &wi) const = 0;

    const BxDFType type;
};


class LambertianReflection: public BxDF {
public:
    explicit LambertianReflection(const Color &albedo) : BxDF(BxDFType::REFLECTION), albedo(albedo) {}

    virtual Color evaluate(Vector3 &wo, Vector3 &wi) const override;
    float computePdf(Vector3 &wo, Vector3 &wi) const override;

private:
    const Color albedo;
};


class SpecularReflection: public BxDF {
public:
    explicit SpecularReflection(const Color &specularColor, const float &ior) :
            BxDF(BxDFType(REFLECTION | SPECULAR)),
            specularColor(specularColor),
            ior(ior) {}

    Color sample(Vector3 &wo, Vector3 &wi, float &pdf) const override;
    Color evaluate(Vector3 &wo, Vector3 &wi) const override { return Color::Black(); }
    float computePdf(Vector3 &wo, Vector3 &wi) const override { return 0; }

private:
    const Color specularColor;
    const float ior;
};

 class SpecularTransmission: public BxDF {
 public:
     explicit SpecularTransmission(const Color &specularColor, const float &ior) :
             BxDF(BxDFType(TRANSMISSION | SPECULAR)),
             specularColor(specularColor),
             ior(ior) {}

     Color sample(Vector3 &wo, Vector3 &wi, float &pdf) const override;
     Color evaluate(Vector3 &wo, Vector3 &wi) const override { return Color::Black(); }
     float computePdf(Vector3 &wo, Vector3 &wi) const override { return 0; }

 private:
     const Color specularColor;
     const float ior;
 };


#endif //BOUNCE_BXDF_HPP
