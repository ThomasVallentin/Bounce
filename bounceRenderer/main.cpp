#include "RayTracer.hpp"
#include "Sphere.h"
#include "FileLoaders.hpp"

#include "fileAdapters/PPMAdapter.hpp"
#include "lights/GradientLight.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/PointLight.hpp"
#include "lights/AreaLight.hpp"

#include <iostream>
#include <accelerators/BVH.hpp>

int intersect_count;

int main() {
    intersect_count = 0;
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int renderWidth = 500;
    int renderHeight = 500;
    float nearClip = 0.001;
    float farClip = 100000;
    int samples = 1;

    Accelerator* accelerator = new BVH;
    Scene scene(accelerator);

    RayTracer tracer(nearClip, farClip, samples);
    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");
    tracer.setAdapter(new PPMAdapter());
//    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

    Shader *mirror = new Metal(.0, .0, .0, .05);
    Shader *greySurface = new SurfaceShader(.2, .2, .2, .05);
    Shader *whiteLambert = new Lambert(.5, .5, .5);
    Shader *redLambert = new Lambert(.8, 0.05, 0.05);
    Shader *greenLambert = new Lambert(0.1, 0.9, 0.1);
    Shader *blueLambert = new Lambert(0.1, 0.1, 0.9);
    Shader *yellowLambert = new Lambert(.9f, .6f, 0.2);

    OBJLoader loader = OBJLoader();

    // Loading the ground
    Transform *transform = Transform::Identity();
//    transform->scale(100, 100, 100);
    loader.setTransform(transform);
    std::string objPath = R"(C:\REPOSITORIES\Bounce\bounceRenderer\ressources\geometries\ground.obj)";
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = whiteLambert;
//        scene.addShape(shape);
    }

    transform = Transform::Identity();
    transform->translate(-1, .5, -3);
    Shape *sphere1 = new Sphere(transform, .5, redLambert);
//    scene.addShape(sphere1);

    transform = Transform::Identity();
//    transform->rotate(Axis::y, degToRad(45));
//    transform->rotate(Axis::x, degToRad(45));
//    transform->translate(0, -2, -7);
    objPath = R"(C:\Users\Thomas Vallentin\Documents\attic2.obj)";
//    objPath = R"(C:\REPOSITORIES\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
    loader.setTransform(transform);
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = whiteLambert;
        scene.addShape(shape);
    }

    transform = Transform::Identity();
    transform->translate(1.5, .3, -6);
    transform->translate(-0.2, 0, 0);
    Shape *sphere2 = new Sphere(transform, .3, mirror);
//    scene.addShape(sphere2);

    transform = Transform::Identity();
    transform->translate(.99, .15, -5.8);
    transform->translate(-0.2, 0, 0);
    Shape *sphere3 = new Sphere(transform, .15, blueLambert);
//    scene.addShape(sphere3);

    transform = Transform::Identity();
    transform->translate(1.25, .1, -5);
    transform->translate(-0.2, 0, 0);
    Shape *sphere4 = new Sphere(transform, .1, greenLambert);
//    scene.addShape(sphere4);

//    EnvironmentLight eLight;
//    eLight.intensity = 0.1f;
//    scene.addLight(&eLight);

    transform = Transform::Identity();
    transform->rotate(Axis::x, degToRad(-20));
    transform->rotate(Axis::y, degToRad(60));
//    transform->rotate(Axis::y, degToRad(20));
    transform->translate(-100, 200, -500);
    PointLight pLight(transform, Color(1.0f, 1.0f, 1.0f), 60000.0f);
    scene.addLight(&pLight);
//    scene.addShape(&dLight);

    transform = Transform::Identity();
//    transform->rotate(Axis::y, degToRad(-45));
//    transform->rotate(Axis::x, degToRad(25));
    transform->rotate(Axis::y, degToRad(120));
    transform->translate(2, 2, -7);
    DiscLight dLight2(transform, .5f, Color(1.0f, 1.0f, 1.0f), 10.0f);
//    scene.addLight(&dLight2);
//    scene.addShape(&dLight2);

    // Camera
    Vector3 from(211, 150, 390), to(211, 100, -500);
    transform = Transform::LookAt(from, to, true);

    Camera cam(transform, 35, FilmGate::Film35mm);
    cam.focusDistance = 1300;
    cam.apertureRadius = 4.0f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);

    // Start rendering
    tracer.trace(&scene);

    std::cout << "intersect_count " << intersect_count << std::endl;

    return (EXIT_SUCCESS);
}
