#include "core/Camera.hpp"


Camera::Camera() : TransformObject(), focalLength(35.0f), apertureRadius(0),
                   filmWidth(FilmGate::Film35mm[0]), filmHeight(FilmGate::Film35mm[1]), filmAspectRatio(filmWidth / filmHeight),
                   renderWidth(1024), renderHeight(576), renderAspectRatio(1024.0f / 576.0f),
                   filmFitMethod(FilmFitMethod::Overscan), focusDistance(1), nearClip(0.001), farClip(100000)
{
    updateAoV();
    updateProjectionPlane();
}


Camera::Camera(const Transform *cameraToWorld, float focalLength, float filmWidth, float filmHeight)
        : TransformObject(cameraToWorld), focalLength(focalLength), apertureRadius(0),
          filmWidth(filmWidth), filmHeight(filmHeight), filmAspectRatio(filmWidth / filmHeight),
          renderWidth(1024), renderHeight(576), renderAspectRatio(1024.0f / 576.0f),
          filmFitMethod(FilmFitMethod::Overscan), focusDistance(1), nearClip(0.001), farClip(100000)
{
    updateAoV();
    updateProjectionPlane();
}

Camera::Camera(const Transform *cameraToWorld, float focalLength, float filmGate[2])
        : TransformObject(cameraToWorld), focalLength(focalLength), apertureRadius(0),
          filmWidth(filmGate[0]), filmHeight(filmGate[1]), filmAspectRatio(filmWidth / filmHeight),
          renderWidth(1024), renderHeight(576), renderAspectRatio(1024.0f / 576.0f),
          filmFitMethod(FilmFitMethod::Overscan), focusDistance(1), nearClip(0.001), farClip(100000)
{
    updateAoV();
    updateProjectionPlane();
}

void Camera::updateProjectionPlane() {
    float ratio;
    if (filmFitMethod == FilmFitMethod::Fill)
        ratio = fminf(float(renderWidth) / filmWidth, float(renderHeight) / filmHeight);
    else
        ratio = fmaxf(float(renderWidth) / filmWidth, float(renderHeight) / filmHeight);

    projectionPlaneWidth = float(renderWidth) / ratio / focalLength * fmaxf(0.001, focusDistance);
    projectionPlaneHeight = projectionPlaneWidth / renderAspectRatio;
    projectionPlaneTopLeftCorner = Vector3(-projectionPlaneWidth / 2.0f, projectionPlaneHeight / 2.0f, -focusDistance);
}

void Camera::generateRay(float u, float v, Ray &ray) const {
    ray.origin = Point3(0, 0, 0);
    if (apertureRadius > 0.0001)  // Aperture is too little, considering it 0 to avoid useless calculations
        ray.origin += randomPointInUnitCircle() * apertureRadius;

//    std::cout << ray.origin << std::endl;
    ray.direction = projectionPlaneTopLeftCorner;
    ray.direction.x += u * projectionPlaneWidth;
    ray.direction.y -= v * projectionPlaneHeight;
    ray.direction -= ray.origin;

    ray.direction.normalize();
    ray.direction *= transform();

    ray.origin.x += transform().matrix.m[3][0];
    ray.origin.y += transform().matrix.m[3][1];
    ray.origin.z += transform().matrix.m[3][2];
}
