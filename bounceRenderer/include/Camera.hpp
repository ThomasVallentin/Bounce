#ifndef CAMERAH
#define CAMERAH

#include "mathUtils.h"
#include "Ray.h"
#include "TransformObject.hpp"

#include <map>

namespace FilmGate {
    static float Film35mm[] = {21.946f, 16.002};
}


enum FilmFitMethod {
    Fill,
    Overscan
};


class Camera : public TransformObject
{
public:
	Camera();
	Camera(const Transform *cameraToWorld, float focalLength, float filmWidth, float filmHeight);
	Camera(const Transform *cameraToWorld, float focalLength, float filmGate[2]);

	// Resolution
	unsigned int *resolution() { static unsigned int res[] = {renderWidth, renderHeight} ; return res; }
	unsigned int width() { return renderWidth; }
	unsigned int height() { return renderHeight; }

	void setResolution(unsigned int w, unsigned int h) {
	    renderWidth = w;
	    renderHeight = h;
	    renderAspectRatio = float(w) / float(h);
        updateProjectionPlane();
	}

    // Film Gate
	float *filmGate() { static float filmG[] = {filmWidth, filmWidth} ; return filmG; }
	void setFilmGate(float (&filmGate)[2]) {
        filmWidth = filmGate[0];
        filmHeight = filmGate[1];
        updateAoV();
        updateProjectionPlane();
	}
	void setFilmGate(float w, float h) {
        filmWidth = w;
        filmHeight = h;
        updateAoV();
        updateProjectionPlane();
	}

	void generateRay(float u, float v, Ray &ray) const;

    float focusDistance, apertureRadius;

protected:
    // == METHODS ==

    void updateAoV() { angleOfView = radToDeg(atanf(0.5f * filmWidth / focalLength) * 2.0f); }
    void updateFLength() { focalLength = filmWidth * 0.5f / (tanf(degToRad(angleOfView))); }
    void updateProjectionPlane();

    // == ATTRIBUTES ==

    float focalLength, angleOfView{};

    // Film and render size
    float filmWidth, filmHeight;
    unsigned int renderWidth{}, renderHeight{};
    float filmAspectRatio, renderAspectRatio{};
    FilmFitMethod filmFitMethod;

    // Virtual projection plane at focus distance to which the rays will be send
	float projectionPlaneWidth{}, projectionPlaneHeight{};
    vector3 projectionPlaneTopLeftCorner;


    float nearClip, farClip;
};

#endif