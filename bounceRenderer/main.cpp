#include "RayTracer.h"
#include "Sphere.h"
#include "TriangleMesh.hpp"
#include "Ray.h"
#include "FileLoaders.hpp"
#include "Transform.hpp"

#include <iostream>

int main() {
    std::cout << "Hello World, Bounce renderer !" << std::endl;

    int output_width = 400;
    int output_height = 200;
    float near_clip = 0.001;
    float far_clip = 100000;
    int samples = 16;

    RayTracer tracer(output_width, output_height, near_clip, far_clip, samples);
    tracer.setOutpath(R"(D:\REPO\Bounce\bounceRenderer\output\output.ppm)");
//    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

    Shader *whiteLambert = new Lambert(.9, .9, .9);
    Shader *redLambert = new Lambert(0.9, 0.1, 0.1);

    // Loading the ground
    OBJLoader loader = OBJLoader();
    std::string objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\ground.obj)";
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = whiteLambert;
        tracer.addShape(shape);
    }

    // Loading the test geometry
    objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = redLambert;
        tracer.addShape(shape);
    }

    // Initialization
    tracer.initialize();

    // Tracing the scene
    Camera cam;
    tracer.trace(cam);

    return (EXIT_SUCCESS);
}


//int main()
//{
//    Matrix4 mat(1, 0, 0, 0,
//                0, 1, 0, 0,
//                0, 0, 1, 0,
//                3, 2, -5, 1);
//    Transform trans(mat);
//
//    vector3 vec(1, 5, -4);
//
//    std::cout << vec << std::endl;
//    vec*= mat;
//    std::cout << vec << std::endl;
//    std::cout << vec * trans.inverseMatrix << std::endl;
//}
