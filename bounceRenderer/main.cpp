#include "core/RayTracer.hpp"
#include "accelerators/BVH.hpp"
#include "samplers/RandomSampler.hpp"
#include "samplers/HierarchicalAdaptive.hpp"

#include "loaders/OBJLoader.hpp"
#include "shapes/Sphere.h"
#include "adapters/PPMAdapter.hpp"

#include "lights/GradientLight.hpp"
#include "lights/DirectionalLight.hpp"
#include "lights/PointLight.hpp"
#include "lights/AreaLight.hpp"

#include "materials/Plastic.hpp"
#include "materials/Lambert.hpp"
#include "materials/Glass.hpp"

#include <iostream>
#include <core/Matrix.hpp>

int main() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int renderWidth = 500;
    int renderHeight = 500;

    float nearClip = 0.002;
    float farClip = 100000;
    unsigned int minSamples = 8;
    unsigned int maxSamples = 128;

    Accelerator* accelerator = new BVH;
    Scene scene(accelerator);

    RayTracer tracer(nearClip, farClip, minSamples, maxSamples);
    tracer.setOutpath(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\output\output.ppm)");
    std::cout << tracer.outpath() << std::endl;
    tracer.setAdapter(new PPMAdapter());
    tracer.setThreadCount(1);
    tracer.setSampler(new RandomSampler());

    Material *bunnyMat = new PlasticMaterial(Color(0, 0, 0),
                                             Color(1, 1, 1));
    Material *glassMat = new GlassMaterial(Color(1, 1, 1),
                                           Color(1, 1, 1), 1.5);
    Material *floorMat = new LambertMaterial(Color(1, 0, 0));
    Material *defaultMat = new LambertMaterial(Color(.5, .5, .5));

    OBJLoader *loader = new OBJLoader();

    Transform *transform = Transform::Identity();
    transform->scale(100, 100, 100);
    transform->translate(25, 100, 0);
    loader->setTransform(transform);

//    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\bunny.obj)", false);
//
//    for (Shape *shape : loader->shapes) {
//        shape->material = glassMat;
//        scene.addShape(shape);
//    }

    scene.addShape(new Sphere(transform, 100, glassMat));

    transform = Transform::Identity();
//    transform->rotate(Axis::x, degToRad(90));
//    transform->rotate(Axis::y, degToRad(30));
    transform->translate(0, 200, -200);

    scene.addShape(new Sphere(transform, 100, defaultMat));

    // Loading the ground
    transform = Transform::Identity();
    transform->scale(100, 100, 100);
    loader->setTransform(transform);
    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\ground.obj)", false);

    for (Shape *shape : loader->shapes) {
        shape->material = floorMat;
        scene.addShape(shape);
    }

    EnvironmentLight *gLight = new EnvironmentLight();
//    gLight->intensity = 0.5f;
    scene.addLight(gLight);

//    transform = Transform::Identity();
//    transform->rotate(Axis::x, degToRad(-20));
//    transform->rotate(Axis::y, degToRad(60));
//    transform->translate(-100, 200, -500);
//    PointLight *pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 60000.0f);
//    scene.addLight(pLight);

    // Camera
    Vector3 from(-250, 120, 550), to(0, 120, 0);
    transform = Transform::LookAt(from, to, true);
//    transform = Transform::Identity();
//    transform->translate(0, 105, 650);

    Camera cam(transform, 25, FilmGate::Film35mm);
    cam.focusDistance = 1300;
    cam.apertureRadius = 0.0f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);

    // Start rendering
    tracer.render(&scene);

    return (EXIT_SUCCESS);
}
