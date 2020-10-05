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


Color LambertianBRDF::evaluate(Vector3 &wo, Vector3 &wi) const {
//    std::cout << "LambertianBRDF::evaluate" << std::endl;
    return albedo / PI;
}


float LambertianBRDF::computePdf(Vector3 &wo, Vector3 &wi) const {
//    std::cout << "LambertianBRDF::computePdf" << std::endl;
    return sameHemisphere(wo, wi) ? absCosTheta(wi) / PI : 0;
}


Color SpecularBRDF::sample(Vector3 &wo, Vector3 &wi, float &pdf) const {
    // Perfect reflection
    wi = Vector3(-wo.x, -wo.y, wo.z);
    pdf = 1;

    return specularColor * fresnelDielectric(cosTheta(wi), 1, ior) / absCosTheta(wi);
}


Color SpecularBRDF::evaluate(Vector3 &wo, Vector3 &wi) const {
//    std::cout << "SpecularBRDF::evaluate"  << std::endl;
    return Color::Black();
}


float SpecularBRDF::computePdf(Vector3 &wo, Vector3 &wi) const {
//    std::cout << "SpecularBRDF::computePdf" << std::endl;
    return 0;
}
