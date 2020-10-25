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

    virtual ~BxDF() {}

    virtual Color sample(const Vector3 &wo, Vector3 &wi, float &pdf) const;
    virtual Color evaluate(const Vector3 &wo, const Vector3 &wi) const = 0;
    virtual float computePdf(const Vector3 &wo, const Vector3 &wi) const = 0;
    virtual std::string toString() const = 0;

    const BxDFType type;
};


class LambertianReflection: public BxDF {
public:
    explicit LambertianReflection(const Color &albedo) : BxDF(BxDFType::REFLECTION), albedo(albedo) {}

    Color evaluate(const Vector3 &wo, const Vector3 &wi) const override;
    float computePdf(const Vector3 &wo, const Vector3 &wi) const override;
    virtual std::string toString() const override { return "BxDF(LambertianReflection)"; }

private:
    const Color albedo;
};


class SpecularReflection: public BxDF {
public:
    explicit SpecularReflection(const Color &specularColor, const float &ior) :
            BxDF(BxDFType(REFLECTION | SPECULAR)),
            specularColor(specularColor),
            ior(ior) {}

    Color sample(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    Color evaluate(const Vector3 &wo, const Vector3 &wi) const override { return Color::Black(); }
    float computePdf(const Vector3 &wo, const Vector3 &wi) const override { return 0; }
    std::string toString() const override { return "BxDF(SpecularReflection)"; }

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

    Color sample(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    Color evaluate(const Vector3 &wo, const Vector3 &wi) const override { return Color::Black(); }
    float computePdf(const Vector3 &wo, const  Vector3 &wi) const override { return 0; }
    std::string toString() const override { return "BxDF(SpecularReflection)"; }

private:
    const Color specularColor;
    const float ior;
};


class Matte: public BxDF {
public:
    explicit Matte(const Color &albedo) :
            BxDF(BxDFType(REFLECTION)),
            albedo(albedo)
            {}

    Color sample(const Vector3 &wo, Vector3 &wi, float &pdf) const override;
    Color evaluate(const Vector3 &wo, const Vector3 &wi) const override { return albedo; }
    float computePdf(const Vector3 &wo, const Vector3 &wi) const override { return 1; }
    std::string toString() const override { return "BxDF(Matte)"; }

private:
    const Color albedo;
};


#endif //BOUNCE_BXDF_HPP
