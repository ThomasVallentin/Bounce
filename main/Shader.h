#ifndef SHADERH
#define SHADERH

#include "Ray.h"
#include "mathUtils.h"

class Shader {

public:
	Shader(const vector3& alb = vector3(0.5, 0.5, 0.5)) { m_albedo = alb; }

	virtual bool scatter(const Ray& ray_in, const HitData& hitdata, vector3& absorbed, Ray& ray_out) const = 0;

	vector3 albedo() const { return m_albedo; }

private:
	vector3 m_albedo;
};


// == LAMBERT =================================================================


class Lambert: public Shader {
public:
	Lambert(const vector3& alb = vector3(.5, .5, .5)) { m_albedo = alb; };

	virtual bool scatter(const Ray& ray_in, const HitData& hitdata, vector3& absorbed, Ray& ray_out) const {
		vector3 direction = hitdata.normal + randPointInUnitSphere();
		
		ray_out = Ray(hitdata.position, direction);
		absorbed = m_albedo;

		return true;
	}

private:
	vector3 m_albedo;
};


// == SURFACE SHADER =================================================================


class SurfaceShader: public Shader {
public:
	SurfaceShader(const vector3& alb = vector3(0.5, 0.5, 0.5), float rough = .2) { m_albedo = alb; m_roughness = rough; }

	virtual bool scatter(const Ray& ray_in, const HitData& hitdata, vector3& absorbedColor, Ray& ray_out) const {
		vector3 direction = reflectVector(ray_in.direction(), hitdata.normal) + randPointInUnitSphere() * m_roughness;

		ray_out = Ray(hitdata.position, direction);
		absorbedColor = m_albedo;
		return (dot(hitdata.normal, direction)) > 0;
	}

private:
	vector3 m_albedo;
	float m_roughness;
};
#endif