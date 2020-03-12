#include "RayTracer.h"
#include "Sphere.h"
#include "TriangleMesh.hpp"
#include "Ray.h"
#include "FileLoaders.hpp"
#include "testGeo.hpp"

#include <iostream>

int main() {
    std::cout << "Hello World, Bounce renderer !" << std::endl;

    int output_width = 600;
    int output_height = 300;
    float near_clip = 0.001;
    float far_clip = 100000;
    int samples = 2;

    RayTracer tracer(output_width, output_height, near_clip, far_clip, samples);
    tracer.setOutpath(R"(D:\REPO\Bounce\bounceRenderer\output\output.ppm)");
//    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

//    // Shaders
//    std::vector<Shader*> shaders;
//    for (unsigned char i=0; i < 25; i++) {
//        shaders.push_back(new Lambert(randomFlt(), randomFlt(), randomFlt()));
//        shaders.push_back(new Metal(randomFlt(), randomFlt(), randomFlt(), randomFlt()));
//        shaders.push_back(new Metal(randomFlt(), randomFlt(), randomFlt(), randomFlt()));
//        shaders.push_back(new Metal(randomFlt(), randomFlt(), randomFlt(), randomFlt()));
//    }
//
    Shader* groundShd = new Lambert(.66, .66, .66);
    Shader* redLambert = new Lambert(0.9, 0.1, 0.1);
//    vector3 pos;
//    float size;
//    Sphere* sph;
//    for (unsigned char i=0; i < 25; i++){
//        size = randomFlt(0, 0.2);
//        pos = vector3(randomFlt(-1, 1)*10, size/2-0.25f, -(randomFlt() * 20 + 1));
//        sph = new Sphere(pos, randomFlt(), shaders[rand() % shaders.size()]);
//        tracer.addHitable(sph);
//    }

    // Creating the ground
    const int groundNbTriangles = 2;
    const int groundNbVertices = 4;
    vector3 groundPoints[4] = {{-100.0, 0.0, -100.0},
                         {-100.0, 0.5, 100.0},
                         {100.0, 0.0, 100.0},
                         {100.0, 0.5, -100.0}};
    const int groundVertexIndices[groundNbTriangles * 3] = {0, 1, 2, 0, 2, 3};
    tracer.addHitable(new TriangleMesh(groundNbTriangles, groundNbVertices, groundVertexIndices, groundPoints, groundShd));

    // Adding geo
//    tracer.addHitable(new TriangleMesh(Fawn::nbTriangles, Fawn::nbVertices, Fawn::vertexIndices, Fawn::positions, redLambert));

    OBJLoader loader = OBJLoader();
    std::string objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
//    std::string objPath = R"(C:\REPOSITORIES\Bounce\bounceRenderer\ressources\geometries\cube.obj)";
    loader.load(objPath, false);

    for (Hitable *hit : loader.hitables)
    {
        hit->shader_ptr = redLambert;
        tracer.addHitable(hit);
    }

    // Initialization
    tracer.initialize();

    // Tracing the scene
    Camera cam;
    tracer.trace(cam);

    return (EXIT_SUCCESS);
}
