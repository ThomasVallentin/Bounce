#ifndef SHADERH
#define SHADERH

#include "Ray.h"
#include "mathUtils.h"

#include <vector>
#include <algorithm>

// == SHADER =============================================================
// Abstract Shader class that has to be inherited and reimplemented
// Shaders's task is to receive a Ray and a HitData in input and returns
// whether it's going to make the light bounce or not.
// If so, it has to fill the outAbsorbtion and outRays with a single
// or multiple absorbtion value and rays that need to be computed.
// =======================================================================
class Shader {

public:
	Shader(const Vector3& alb = Vector3(0.5, 0.5, 0.5)) { m_albedo = alb; }

	virtual bool scatter(const Ray& inRay, const HitData& hitdata, std::vector<Vector3>& outAbsorbtion, std::vector<Ray>& outRays) const = 0;

	// Vector3 albedo() const { return m_albedo; }

private:
	Vector3 m_albedo;
};


// == LAMBERT =================================================================


class Lambert: public Shader {
public:
	Lambert(const Vector3& alb = Vector3(.5, .5, .5)) { m_albedo = alb; };
	Lambert(float albR, float albG, float albB) { m_albedo = Vector3(albR, albG, albB); };

	bool scatter(const Ray& inRay, const HitData& hitdata, std::vector<Vector3>& outAbsorbtion, std::vector<Ray>& outRays) const override {
		Vector3 direction(hitdata.normal + randPointInUnitSphere());
		Vector3 absorbtion(m_albedo);

		outRays.push_back(Ray(hitdata.position, direction));
		outAbsorbtion.push_back(m_albedo);

		return true;
	}

private:
	Vector3 m_albedo;
};


// == METAL =======================================================================


class Metal: public Shader {
public:
	Metal(const Vector3& alb = Vector3(.5, .5, .5), float rough = 0.2) { m_albedo = alb; m_roughness = rough; }
	Metal(float albR, float albG, float albB, float rough) { m_albedo = Vector3(albR, albG, albB); m_roughness = rough; };

	bool scatter(const Ray& inRay, const HitData& hitdata, std::vector<Vector3>& outAbsorbtion, std::vector<Ray>& outRays) const override {
		Vector3 direction = reflectVector(inRay.direction, hitdata.normal) + randPointInUnitSphere() * m_roughness;

		outRays.push_back(Ray(hitdata.position, direction));
		outAbsorbtion.push_back(m_albedo);
		return (dot(hitdata.normal, direction)) > 0;
	}

private:
	Vector3 m_albedo;
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
		outVector = iorRatio * (in + surfaceNormal*cosIn) - surfaceNormal * sqrtf(discriminant);
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


class Glass: public Shader {
public:
	Glass() { m_reflectColor = Vector3(1, 1, 1); m_refractColor = Vector3(1, 1, 1); m_ior = 1.3; };

	bool scatter(const Ray& inRay, const HitData& hitdata, std::vector<Vector3>& outAbsorbtion, std::vector<Ray>& outRays) const override {
		
		float reflectRatio = fresnel(inRay.direction, hitdata.normal, m_ior);
		bool outside = dot(inRay.direction, hitdata.normal) < 0;

		const Vector3 bias = 0.000001f * hitdata.normal;

		bool isRefracting = false;
		if (reflectRatio < 1) {  // if we're not in a total internal reflection
			Vector3 refracted;
			isRefracting = refract(inRay.direction, hitdata.normal, m_ior, refracted);
			Vector3 refractOrigin = outside ? hitdata.position - bias : hitdata.position + bias;

			outRays.push_back(Ray(refractOrigin, refracted));
			outAbsorbtion.push_back(m_refractColor * (1 - reflectRatio));
		}

		Vector3 reflected = reflectVector(inRay.direction, hitdata.normal);
		Vector3 reflectOrigin = outside ? hitdata.position + bias : hitdata.position - bias;

		//outRays.push_back(Ray(reflectOrigin, reflected));
		//outAbsorbtion.push_back(m_reflectColor * reflectRatio);

		return isRefracting;
	}

private:
	Vector3 m_reflectColor;
	Vector3 m_refractColor;

	float m_ior;

};


// == SURFACE SHADER =================================================================


class SurfaceShader: public Shader {
public:
	SurfaceShader(const Vector3& alb = Vector3(.5, .5, .5), float rough = 0.2) { m_albedo = alb; m_roughness = rough; }
	SurfaceShader(float albR, float albG, float albB, float rough) { m_albedo = Vector3(albR, albG, albB); m_roughness = rough;};

	bool scatter(const Ray& inRay, const HitData& hitdata, std::vector<Vector3>& outAbsorbtion, std::vector<Ray>& outRays) const override {
		Vector3 direction = reflectVector(inRay.direction, hitdata.normal) + randPointInUnitSphere() * m_roughness;

		outRays.push_back(Ray(hitdata.position, direction));
		outAbsorbtion.push_back(m_albedo);
		return (dot(hitdata.normal, direction)) > 0;
	}

private:
	Vector3 m_albedo;
	float m_roughness;
};



#endif