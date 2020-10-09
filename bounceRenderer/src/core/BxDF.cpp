//
// Created by Thomas Vallentin on 23/09/2020.
//
#include "core/BxDF.hpp"


bool sameHemisphere(const Vector3 &v1, const Vector3 &v2) {
    return v1.z * v2.z > 0;
}



Color BxDF::sample(Vector3 &wo, Vector3 &wi, float &pdf) const {
//    std::cout << "  BxDF::sample" << std::endl;
    wi = cosineSampleHemisphere();
    pdf = computePdf(wo, wi);

    return evaluate(wo, wi);
}


Color LambertianReflection::evaluate(Vector3 &wo, Vector3 &wi) const {
//    std::cout << "LambertianReflection::evaluate" << std::endl;
    return albedo / PI;
}


float LambertianReflection::computePdf(Vector3 &wo, Vector3 &wi) const {
//    std::cout << "LambertianReflection::computePdf" << std::endl;
    return sameHemisphere(wo, wi) ? absCosTheta(wi) / PI : 0;
}


Color SpecularReflection::sample(Vector3 &wo, Vector3 &wi, float &pdf) const {
    // Perfect reflection
    wi = Vector3(-wo.x, -wo.y, wo.z);
    pdf = 1;

    return specularColor * fresnelDielectric(cosTheta(wi), 1,  ior) / absCosTheta(wi);
}


Color SpecularTransmission::sample(Vector3 &wo, Vector3 &wi, float &pdf) const {
    bool entering = cosTheta(wo) > 0.0f;

    float etaI = entering ? 1 : ior;
    float etaT = entering ? ior : 1;
    Vector3 n = entering ? Vector3(0, 0, 1) : Vector3(0, 0, -1);
    if (!refract(wo, n, etaI / etaT, wi)){
        pdf = 0;
        return Color::Black();
    }

    pdf = 1;
    return specularColor * (1 - fresnelDielectric(cosTheta(wi), 1, ior)) / absCosTheta(wi);
}
