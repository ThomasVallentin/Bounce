#ifndef SHADERH
#define SHADERH

#include "Light.hpp"
#include "Color.hpp"
#include "mathUtils.h"

#include <vector>
#include <algorithm>

class Light;

class Scene;

// == SHADER =============================================================
// Abstract Shader class that has to be inherited and reimplemented
// Shaders's task is to receive a Ray and a HitData in input and returns
// whether it's going to make the light bounce or not.
// If so, it has to fill the outAbsorbtion and outRays with a single
// or multiple absorbtion value and rays that need to be computed.
// =======================================================================
class Shader {

public:
    Shader(const Color &alb) { albedo = alb; emission=Color::Black(); }

    virtual bool sampleDiffusion(const Ray &inRay, const HitData &hitdata, Ray& outRay, Color& absorbance) {
        return false;
    }
    virtual bool sampleReflection(const Ray &inRay, const HitData &hitdata, Ray& outRay, Color& absorbance) {
        return false;
    }
    virtual bool sampleTransmission(const Ray &inRay, const HitData &hitdata, Ray& outRay, Color& absorbance) {
        return false;
    }
    virtual Color sampleEmission(const Ray &inRay, const HitData &hitdata) {
        return emission;
    }

    Color emission;
protected:
    Color albedo;
};


// == LAMBERT =================================================================


class Lambert: public Shader {
public:
	explicit Lambert(const Color& alb) : Shader(alb) {}
	Lambert(float albR, float albG, float albB) : Shader(Color(albR, albG, albB)) {}

    bool sampleDiffusion(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override;
};


// == METAL =======================================================================


class Metal: public Shader {
public:
	Metal(const Color& alb, float rough) : Shader(alb), m_roughness(rough) {}
	Metal(float albR, float albG, float albB, float rough)  : Shader(Color(albR, albG, albB)), m_roughness(rough) {}

	bool sampleReflection(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override;

protected:
	float m_roughness;
};


// == REFRACT-FRESNEL =================================================================


inline bool refract(const Vector3& in, const Vector3& surfaceNormal, float surfaceIor, Vector3& outVector) {
	float cosIn = dot(in, surfaceNormal);
	float iorIn = 1, iorOut = surfaceIor;
	Vector3 normal = surfaceNormal;
	if (cosIn < 0) {
		// hit the surface in the opposite direction of the surface 
		//cosIn = -cosIn;
	}
	else {
		// hit the surface in the same direction as the surface normal (backface)
		// -> flipping the normal to have it facing the inVector
		// -> swapping ior order since we are actually inside the hitSurface
		normal = -normal;
        std::swap(iorIn, iorOut);
	}
	float iorRatio = iorIn / iorOut;
	float discriminant = 1 - iorRatio * iorRatio * (1 - cosIn * cosIn);

	if (discriminant < 0) {
		return false;
	}
	else {
		//outVector = iorRatio * in + surfaceNormal * (iorRatio * cosIn - sqrtf(discriminant));
		outVector =  (in + surfaceNormal*cosIn) * iorRatio - surfaceNormal * sqrtf(discriminant);
		return true;
	}
}

inline float fresnel(const Vector3& in, const Vector3& surfaceNormal, float ior) {
	float cosIn = dot(in, surfaceNormal);
	float iorIn = 1, iorOut = ior;
	if (cosIn > 0) {
		// hit the surface in the opposite direction of the surface normal
		// -> inverting cosIn to get a positive value
        std::swap(iorIn, iorOut);
	}

	// computing sinus using Snell's law
	float sinOut = iorIn / iorOut * sqrtf(std::max(0.f, 1 - cosIn * cosIn)) ;

	if (sinOut >= 1) {
		// Total intern reflection
		return 1;
	}
	else {
		float cosOut = sqrtf(std::max(0.f, 1 - sinOut * sinOut));
		cosIn = fabsf(cosIn);
		float reflectRatio = (iorOut * cosIn - iorIn * cosOut) / (iorOut * cosIn + iorIn * cosOut);
		float refractRatio = (iorIn * cosOut - iorOut * cosIn) / (iorIn * cosOut + iorOut * cosIn);
		return (reflectRatio * reflectRatio + refractRatio * refractRatio) / 2;
	}
}


// == GLASS SHADER =================================================================


//class Glass: public Shader {
//public:
//	Glass() : Shader(Color()),
//              m_reflectColor(Color(1, 1, 1)),
//              m_refractColor(Color(1, 1, 1)),
//              m_ior(1.3) {}
//
//    bool sampleDiffusion(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override {
//        // We compute the reflect/refract ratio that will be used in sampleReflection & sampleTransmission
//        reflectRatio = fresnel(inRay.direction, hitdata.normal, m_ior);
//
//    }
//    bool sampleReflection(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override;
//    bool sampleTransmission(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override;
//
//protected:
//    Color m_reflectColor;
//    Color m_refractColor;
//
//	float m_ior;
//
//private:
//    float reflectRatio;
//};


// == SURFACE SHADER =================================================================


class SurfaceShader: public Shader {
public:
    SurfaceShader(const Color& alb, float rough) : Shader(alb), m_roughness(rough) {}
    SurfaceShader(float albR, float albG, float albB, float rough)  : Shader(Color(albR, albG, albB)), m_roughness(rough) {}

    bool sampleDiffusion(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override;
    bool sampleReflection(const Ray& inRay, const HitData& hitdata, Ray& outRay, Color& absorbance) override;

protected:
	float m_roughness;
};


// == LIGHT SHADER =================================================================


class LightShader : public Shader {
public:
    explicit LightShader(const Light *light) : Shader(Color::Black()), light(light) {}

    virtual Color sampleEmission(const Ray &inRay, const HitData &hitdata) override;

    const Light *light;
};

#endif