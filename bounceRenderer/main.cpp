#include "RayTracer.h"
#include "Sphere.h"
#include "FileLoaders.hpp"

#include <iostream>

int main() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int renderWidth = 1000;
    int renderHeight = 1000;
    float nearClip = 0.001;
    float farClip = 100000;
    int samples = 50;

    Scene scene;

    RayTracer tracer(nearClip, farClip, samples);
    tracer.setOutpath(R"(D:\REPO\Bounce\bounceRenderer\output\output.ppm)");
//    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

    Shader *darkMirrorShader = new SurfaceShader(.1, .1, .1, 0);
    Shader *greyLambert = new Lambert(.2, .2, .2);
    Shader *redLambert = new Lambert(.8, 0.05, 0.05);
    Shader *greenLambert = new Lambert(0.1, 0.9, 0.1);
    Shader *blueLambert = new Lambert(0.1, 0.1, 0.9);

    // Loading the ground
    Transform *transform = Transform::Identity();
    transform->scale(10, 10, 10);

    OBJLoader loader = OBJLoader(transform);
    std::string objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\ground.obj)";
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = greyLambert;
        scene.addShape(shape);
    }

    transform = Transform::Identity();
    transform->translate(0, 1, -7);
    Shape *sphere1 = new Sphere(transform, 1, redLambert);
    scene.addShape(sphere1);

    transform = Transform::Identity();
    transform->rotate(Axis::y, degToRad(45));
    transform->rotate(Axis::x, degToRad(45));
    transform->translate(0, 3, -7);
    objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\cube.obj)";
    loader.setTransform(transform);
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = greenLambert;
        scene.addShape(shape);
    }

    transform = Transform::Identity();
    transform->translate(1, 1, -12);
    Shape *sphere2 = new Sphere(transform, 1, greenLambert);
    scene.addShape(sphere2);

    transform = Transform::Identity();
    transform->translate(-1, 1, -2);
    Shape *sphere3 = new Sphere(transform, 1, blueLambert);
    scene.addShape(sphere3);

    transform = Transform::Identity();
    transform->translate(2, 5, -7);
    Light *pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 10.0f);
    scene.addLight(pLight);

    // Camera
    Vector3 from(0, 1.2, 11), to(0, 1.2, -7);
    transform = Transform::LookAt(from, to, true);

    Camera cam(transform, 35, FilmGate::Film35mm);
    cam.focusDistance = (to - from).length();
    cam.apertureRadius = 0.0f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);

    // Initialization
    tracer.initialize();

    // Start rendering
    tracer.trace(&scene);

    return (EXIT_SUCCESS);
}
