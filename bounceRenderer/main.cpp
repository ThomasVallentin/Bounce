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
#include "lights/DiscLight.hpp"

#include "materials/Plastic.hpp"
#include "materials/Lambert.hpp"
#include "materials/Glass.hpp"

#include <iostream>
#include <core/Matrix.hpp>

int main() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int renderWidth = 500;
    int renderHeight = 500;

    float nearClip = 0.0001;
    float farClip = 100000;
    unsigned int minSamples = 8;
    unsigned int maxSamples = 8;

    Accelerator* accelerator = new BVH;
    Scene scene(accelerator);

    RayTracer tracer(nearClip, farClip, minSamples, maxSamples);
    tracer.setOutpath(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\output\output.ppm)");
    std::cout << tracer.outpath() << std::endl;
    tracer.setAdapter(new PPMAdapter());
    tracer.setThreadCount(1);
    tracer.setSampler(new RandomSampler());

    Material *bunnyMat = new PlasticMaterial(Color(.8, .8, .8),
                                             Color(0, 0, 0));
    Material *glassMat = new GlassMaterial(Color(1, 1, 1),
                                           Color(1, 1, 1), 1.5);
    Material *floorMat = new LambertMaterial(Color(.8, .8, .8));
    Material *defaultMat = new LambertMaterial(Color(.5, .5, .5));

    OBJLoader *loader = new OBJLoader();
    Transform *transform;

    transform = Transform::Identity();
    transform->scale(100, 100, 100);
    transform->translate(25, 0, 0);
    loader->setTransform(transform);

    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\bunny.obj)", false);
//    loader->shapes[0]->material = bunnyMat;
//    scene.addShape(loader->shapes[0]);

    for (Shape *shape : loader->shapes) {
        shape->material = bunnyMat;
        scene.addShape(shape);
    }

//    transform = Transform::Identity();
//    transform->scale(100, 100, 100);
//    transform->translate(25, 0, 0);
//    loader->setTransform(transform);
//    scene.addShape(new Sphere(transform, 100, defaultMat));

//    transform = Transform::Identity();
//    transform->rotate(Axis::x, degToRad(90));
//    transform->rotate(Axis::y, degToRad(30));
//    transform->translate(0, 200, -200);

//    scene.addShape(new Sphere(transform, 100, defaultMat));

    // Loading the ground
    transform = Transform::Identity();
    transform->scale(100, 100, 100);
    loader->setTransform(transform);
    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\ground.obj)", false);

    for (Shape *shape : loader->shapes) {
        shape->material = bunnyMat;
        scene.addShape(shape);
    }

//    EnvironmentLight *gLight = new EnvironmentLight();
//    gLight->intensity = 0.2f;
//    scene.addLight(gLight);

    transform = Transform::Identity();
    transform->rotate(Axis::x, degToRad(-20));
    transform->rotate(Axis::y, degToRad(-145));
    transform->translate(100, 200, 100);
    Light *pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 10000);
//    scene.addLight(pLight);

    transform = Transform::Identity();
    transform->rotate(Axis::x, degToRad(-90));
//    transform->rotate(Axis::y, degToRad(180));
    transform->translate(0, 300, 0);
    AreaLight *areaLight = new DiscLight(transform, 100, Color(1.0f, 1.0f, 1.0f), 200 * powf(2, 6), 2);
    scene.addLight(areaLight);
//    scene.addShape(areaLight->shape);
//    scene.addShape(new Disc(transform, 50, bunnyMat));

    // Camera
    Vector3 from(-250, 120, 550), to(0, 100, 0);
    transform = Transform::LookAt(from, to, true);
//    transform = Transform::Identity();
//    transform->translate(0, 105, 650);

    Camera cam(transform, 15, FilmGate::Film35mm);
    cam.focusDistance = 1300;
    cam.apertureRadius = 0.0f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);

    // Start rendering
    tracer.render(&scene);

    return (EXIT_SUCCESS);
}
