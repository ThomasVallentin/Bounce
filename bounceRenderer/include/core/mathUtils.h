#ifndef MATHUTILSH
#define MATHUTILSH

#define PI 3.14159265f

#include "Ray.h"
#include <cmath>
#include <cstdlib>
#include <random>

static std::default_random_engine engine;
static std::uniform_real_distribution<float> uniform(0.0f, 1.0f);

extern float degToRad(const float deg);
extern float radToDeg(const float rad);

inline float clamp(const float &x, const float &min, const float &max) {
    return std::min(std::max(x, min), max);
}

extern float randomFlt(float a=0, float b=1);
extern Vector3 randomPointInUnitCircle();
extern Vector3 randomPointInUnitSphere();
extern Vector3 cosineSampleHemisphere();

extern void makeCoordinateSystem(const Vector3 &N, Vector3 &tan1, Vector3 &tan2);
extern Vector3 worldToLocal(const Vector3 &vec, const Vector3 &vx, const Vector3 &vy, const Vector3 &vz);
extern Vector3 localToWorld(const Vector3 &vec, const Vector3 &vx, const Vector3 &vy, const Vector3 &vz);

extern float schlickFresnel(const float &cosTheta, const float &eta1, const float &eta2);
extern float fresnelDielectric(float cosThetaI, float eta1, float eta2);
extern bool refract(const Vector3 &wI, const Vector3 &N, const float eta, Vector3& wT);

extern bool intersectPlane(const Ray& ray, const Vector3& normal, const Point3& pointOnPlane, float& outParameter);
extern bool intersectDisk(const Ray& ray, const Vector3& normal, const float &radius, const Point3& center, float& outParameter);

#endif