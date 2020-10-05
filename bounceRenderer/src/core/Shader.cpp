#include "core/Shader.hpp"

bool Lambert::sampleDiffusion(const Ray &inRay, const HitData &hitdata, Ray &outRay, Color &absorbance) {
    Vector3 direction(hitdata.normal + randomPointInUnitSphere());

    outRay = Ray(hitdata.position, direction);
    absorbance = albedo * std::max(0.0f, dot(hitdata.normal, outRay.direction));

    return true;
}

bool Metal::sampleReflection(const Ray &inRay, const HitData &hitdata, Ray &outRay, Color &absorbance) {
    Vector3 direction = reflectVector(inRay.direction, hitdata.normal) + randomPointInUnitSphere() * m_roughness;

    // Avoid computing the ray if reflected ray has a direction opposed to the surface normal
    if ((dot(hitdata.normal, direction)) <= 0)
        return false;

    outRay = Ray(hitdata.position, direction);
    absorbance = Color(1.0f);

    return true;
}

//bool Glass::sampleReflection(const Ray &inRay, const HitData &hitdata, Ray &outRay, Color &absorbance) {
//    bool outside = dot(inRay.direction, hitdata.normal) < 0;
//
//    const Vector3 bias = hitdata.normal * 0.000001f;
//
//    Point3 reflectOrigin = outside ? hitdata.position + bias : hitdata.position - bias;
//    outRay = Ray(reflectOrigin, reflectVector(inRay.direction, hitdata.normal));
//    absorbance = m_reflectColor * reflectRatio;
//
//    return true;
//}
//
//bool Glass::sampleTransmission(const Ray &inRay, const HitData &hitdata, Ray &outRay, Color &absorbance) {
//    bool outside = dot(inRay.direction, hitdata.normal) < 0;
//    const Vector3 bias = hitdata.normal * 0.000001f;
//
//    if (reflectRatio >= 1) // return if we're in a total internal reflection
//        return false;
//
//    Vector3 refracted;
//    bool isRefracting = refract(inRay.direction, hitdata.normal, m_ior, refracted);
//    Vector3 refractOrigin = outside ? hitdata.position - bias : hitdata.position + bias;
//
//    outRay = Ray(refractOrigin, refracted);
//    absorbance = m_refractColor * (1 - reflectRatio);
//
//    return isRefracting;
//}

bool SurfaceShader::sampleDiffusion(const Ray &inRay, const HitData &hitdata, Ray &outRay, Color &absorbance) {
    // Lambert diffusion
    Vector3 direction(hitdata.normal + randomPointInUnitSphere());

    outRay = Ray(hitdata.position, direction);
    absorbance = albedo * std::max(0.0f, dot(hitdata.normal, outRay.direction));

    return true;
}


bool SurfaceShader::sampleReflection(const Ray &inRay, const HitData &hitdata, Ray &outRay, Color &absorbance) {
    Vector3 direction = (reflectVector(inRay.direction, hitdata.normal) + randomPointInUnitSphere() * m_roughness).normalized();

//    Avoid computing the ray if reflected ray has a direction opposed to the surface normal
    float incidence = dot(hitdata.normal, direction);
    if (incidence <= 0)
        return false;

    outRay = Ray(hitdata.position, direction);
    absorbance = Color(incidence, incidence, incidence);

    return true;
}

Color LightShader::sampleEmission(const Ray &inRay, const HitData &hitdata) {
    return 1;
}
