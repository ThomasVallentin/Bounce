#include "core/mathUtils.h"


float degToRad(const float deg) {
    return PI / 180.0f  * deg;
}

float radToDeg(const float rad) {
    return rad * 180.0f / PI;
}

float randomFlt(float a, float b) {
	float rnd = uniform(engine);
	float diff = b - a;
	return rnd * diff + a;
}

Vector3 randomPointInUnitCircle() {
    Vector3 point;
    do {
        point = Vector3(randomFlt(), randomFlt(), 0.0f) * 2.0f  - Vector3(1, 1, 0);
    } while (point.squaredLength() >= 1.0);

    return point;
}

Vector3 randomPointInUnitSphere() {
	Vector3 point;
	do {
		point = Vector3(randomFlt(), randomFlt(), randomFlt()) * 2.0f - Vector3(1, 1, 1);
	} while (point.squaredLength() >= 1.0);

	return point;
}


Vector3 cosineSampleHemisphere() {
    float r1 = uniform(engine), r2 = uniform(engine);
    return Vector3(std::cos(2 * PI * r1) * sqrtf(1 - r2),
                   std::sin(2 * PI * r1) * sqrtf(1 - r2),
                   sqrtf(r2));
}


void makeCoordinateSystem(const Vector3& N, Vector3 &tan1, Vector3 &tan2) {
    if ( std::abs(N.x) > std::abs(N.y) ) {
        tan1 = Vector3(-N.z, 0.0f, N.x) / std::sqrt(N.x * N.x + N.z * N.z);
    } else {
        tan1 = Vector3(0.0f, -N.z, N.y) / std::sqrt(N.y * N.y + N.z * N.z);
    }
    tan2 = cross(N, tan1);
}


Vector3 worldToLocal(const Vector3 &vec, const Vector3 &vx, const Vector3 &vy, const Vector3 &vz) {
    return Vector3(dot(vec, vx), dot(vec, vy), dot(vec, vz));
}


Vector3 localToWorld(const Vector3 &vec, const Vector3 &vx, const Vector3 &vy, const Vector3 &vz) {
    return Vector3(vx.x * vec.x + vy.x * vec.y + vz.x * vec.z,
                   vx.y * vec.x + vy.y * vec.y + vz.y * vec.z,
                   vx.z * vec.x + vy.z * vec.y + vz.z * vec.z);
}


float schlickFresnel(const float &eta1, const float &eta2, const float &cosTheta) {
    float r0 = powf((eta1 - eta2) / (eta1 + eta2), 2);
    return r0 + (1 - r0) * powf((1 - cosTheta), 5);
}


float fresnelDielectric(float cosThetaI, float etaI, float etaT) {
    if (cosThetaI < 0) {
        // hit the surface in the opposite direction of the surface normal
        // -> inverting cosIn to get a positive value
        std::swap(etaI, etaT);
        cosThetaI = std::abs(cosThetaI);
    }
    // computing sinus using Snell's law
    float sinThetaI =  sqrtf(std::max(0.f, 1 - cosThetaI * cosThetaI));
    float sinThetaT = etaI / etaT * sinThetaI;

    if (sinThetaT >= 1) {
        return 1;
    }

    float cosThetaT = sqrtf(std::max(0.f, 1 - sinThetaT * sinThetaT));
    float Rs = (etaT * cosThetaI - etaI * cosThetaT) / (etaT * cosThetaI + etaI * cosThetaT);
    float Rp = (etaI * cosThetaI - etaT * cosThetaT) / (etaI * cosThetaI + etaT * cosThetaT);
    return  (Rs * Rs + Rp * Rp) / 2;
}


bool refract(const Vector3 &wI, const Vector3 &N, const float eta, Vector3& wT) {
    float cosThetaI = dot(N, wI);
    float sin2ThetaI = std::max(0.0f, 1 - cosThetaI * cosThetaI);
    float sin2ThetaT = eta * eta * sin2ThetaI;

    if (sin2ThetaT >= 1)
        return false;

    float cosThetaT = std::sqrt(1 - sin2ThetaT);
    wT = wI * (-eta) + N * (eta * cosThetaI - cosThetaT);

    return true;
}


bool intersectPlane(const Ray& ray, const Vector3& normal, const Point3& pointOnPlane, float& outParameter) {
    float a = dot(normal, ray.direction);

    if (a < 0.000001)
        return false;

    Vector3 b(pointOnPlane - ray.origin);
    outParameter = dot(b, normal) / a;

    return outParameter >= 0;
}

bool intersectDisk(const Ray& ray, const Vector3& normal, const float& radius, const Point3& center, float& outParameter) {
    if (!intersectPlane(ray, normal, center, outParameter))
        return false;

    Vector3 centerToHit = center - (ray.origin + ray.direction * outParameter);
    return centerToHit.squaredLength() <= (radius * radius);
}