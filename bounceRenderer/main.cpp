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
#include "core/mathUtils.h"

#include <iostream>
#include <core/Matrix.hpp>

int main() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int renderWidth = 500;
    int renderHeight = 500;

    float nearClip = 0.002;
    float farClip = 100000;
    unsigned int minSamples = 8;
    unsigned int maxSamples = 32;

    Accelerator* accelerator = new BVH;
    Scene scene(accelerator);

    RayTracer tracer(nearClip, farClip, minSamples, maxSamples);
    tracer.setOutpath(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\output\output.ppm)");
    tracer.setAdapter(new PPMAdapter());
    tracer.setThreadCount(8);
    tracer.setSampler(new RandomSampler());
    //    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

    Material *white = new PlasticMaterial(Color(.8, 0.08, 0.05),
                                                 Color(1, 1, 1));

    Material *red = new LambertMaterial(Color(.8, 0.8, 0.8));

    OBJLoader *loader = new OBJLoader();

    Transform *transform = Transform::Identity();
    transform->scale(100, 100, 100);
//    transform->rotate(Axis::x, degToRad(90));
//    transform->rotate(Axis::y, degToRad(30));
    transform->translate(250, -50, -500);
    loader->setTransform(transform);

    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\bunny.obj)", false);

    for (Shape *shape : loader->shapes) {
        shape->material = white;
        scene.addShape(shape);
    }

    // Loading the ground
    transform = Transform::Identity();
    transform->scale(100, 100, 100);
    transform->translate(280, -50, -500);
    loader->setTransform(transform);
    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\ground.obj)", false);

    for (Shape *shape : loader->shapes) {
        shape->material = red;
        scene.addShape(shape);
    }

    GradientLight *gLight = new GradientLight();
    gLight->intensity = 0.5f;
    scene.addLight(gLight);

//    transform = Transform::Identity();
//    transform->rotate(Axis::x, degToRad(-20));
//    transform->rotate(Axis::y, degToRad(60));
//    transform->translate(-100, 200, -500);
//    PointLight *pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 60000.0f);
//    scene.addLight(pLight);

    // Camera
    Vector3 from(211, 150, 390), to(211, 100, -500);
    transform = Transform::LookAt(from, to, true);

    Camera cam(transform, 35, FilmGate::Film35mm);
    cam.focusDistance = 1300;
    cam.apertureRadius = 0.0f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);

    // Start rendering
    tracer.render(&scene);

    return (EXIT_SUCCESS);
}
