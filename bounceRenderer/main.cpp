//#include "core/RayTracer.hpp"
//#include "core/Texture.hpp"
//#include "accelerators/BVH.hpp"
//#include "samplers/RandomSampler.hpp"
//#include "samplers/HierarchicalAdaptive.hpp"
//#include "loaders/OBJLoader.hpp"
//#include "shapes/Sphere.h"
//#include "adapters/PPMAdapter.hpp"
//
//#include "lights/GradientLight.hpp"
//#include "lights/DirectionalLight.hpp"
//#include "lights/PointLight.hpp"
//#include "lights/DiscLight.hpp"
//
//#include "materials/Plastic.hpp"
//#include "materials/Lambert.hpp"
//#include "materials/Glass.hpp"
#include "core/Texture.hpp"

//#include <iostream>

int main() {
    ImageTexture<Color> texture(R"(C:\Users\Thomas Vallentin\Pictures\Adobe-Photoshop-CC-2015-Logo-ICon.png)");
    std::cout << texture.sample(.05, .05) << std::endl;

//    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;
//
//    int renderWidth = 16*10;
//    int renderHeight = 9*10;
//
//    float nearClip = 0.0001;
//    float farClip = 100000;
//    unsigned int minSamples = 10;
//    unsigned int maxSamples = 10;
//
//    Accelerator* accelerator = new BVH;
//    Scene scene(accelerator);
//
//    RayTracer tracer(nearClip, farClip, minSamples, maxSamples);
//    tracer.setOutpath(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\output\output.png)");
//    std::cout << tracer.outpath() << std::endl;
//
//
//    tracer.setThreadCount(8);
//    tracer.setSampler(new RandomSampler());
//
//    Material *bunnyMat = new PlasticMaterial(Color(.8, .8, .8),
//                                             Color(0, 0, 0));
//    Material *glassMat = new GlassMaterial(Color(1, 1, 1),
//                                           Color(1, 1, 1), 1.5);
//    Material *floorMat = new LambertMaterial(Color(0, 0, 0));
//    Material *defaultMat = new LambertMaterial(Color(.5, .5, .5));
//
//    OBJLoader *loader = new OBJLoader();
//    Transform *transform;
//
//    transform = Transform::Identity();
//    loader->setTransform(transform);
//    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\attic_4.obj)", false);
//    for (Shape *shape : loader->shapes) {
//        shape->material = defaultMat;
//        scene.addShape(shape);
//    }
//
//    transform = Transform::Identity();
//    transform->scale(100, 100, 100);
//    transform->rotate(Axis::x, degToRad(90));
//    transform->translate(220, 0, 130);
//    loader->setTransform(transform);
//    loader->load(std::string(getenv("BOUNCE_ROOT")) + R"(\bounceRenderer\ressources\geometries\ground.obj)", false);
//    for (Shape *shape : loader->shapes) {
//        shape->material = floorMat;
//        scene.addShape(shape);
//    }
//
//    Light *gLight = new GradientLight();
//    gLight->intensity = .5f;
////    scene.addLight(gLight);
//
//    transform = Transform::Identity();
////    transform->rotate(Axis::y, degToRad(100));
////    transform->rotate(Axis::z, degToRad(30));
//    transform->translate(-500*2.8, 550*2, -200);
//    Light *pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 20000 * powf(2, 8));
////    scene.addLight(pLight);
//
//    transform = Transform::Identity();
//    transform->translate(220, 350, -500);
//    pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 4000);
////    scene.addLight(pLight);
//
//    transform = Transform::Identity();
//    transform->rotate(Axis::y, degToRad(100));
//    transform->rotate(Axis::z, degToRad(30));
//    transform->translate(-500*2.8, 550*2, -200);
//    AreaLight *areaLight = new DiscLight(transform, 75, Color(1.0f, 1.0f, 1.0f), 80000 * powf(2, 7), 1);
//    scene.addLight(areaLight);
////    scene.addShape(areaLight->shape);
////    scene.addShape(new Disc(transform, 50, bunnyMat));
//
//    // Camera
//    transform = Transform::Identity();
//    transform->rotate(Axis::z, degToRad(2.8));
//    transform->rotate(Axis::x, degToRad(6.5));
//    transform->translate(221, 179, 125);
//
//    Camera cam(transform, 18, FilmGate::Film35mm);
//    cam.focusDistance = 780;
//    cam.apertureRadius = 3.2f;
//    cam.setResolution(renderWidth, renderHeight);
//
//    tracer.setCamera(cam);
//
//    // Start rendering
////    tracer.render(&scene);
//    tracer.initialize(&scene);
//    tracer.writeImage();

    return (EXIT_SUCCESS);
}
