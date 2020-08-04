#include "RayTracer.h"
#include "Sphere.h"
#include "FileLoaders.hpp"

#include <iostream>

int main() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int output_width = 200;
    int output_height = 100;
    float near_clip = 0.001;
    float far_clip = 100000;
    int samples = 1;

    RayTracer tracer(output_width, output_height, near_clip, far_clip, samples);
    tracer.setOutpath(R"(D:\REPO\Bounce\bounceRenderer\output\output.ppm)");
//    tracer.setOutpath(R"(C:\REPOSITORIES\Bounce\bounceRenderer\output\output.ppm)");

    Shader *whiteLambert = new SurfaceShader(.9, .9, .9, 0);
    Shader *redLambert = new Lambert(.9, 0.1, 0.1);

    // Loading the ground
    Transform *transform = Transform::Identity();
    transform->rotate(Axis::y, degToRad(45));

    OBJLoader loader = OBJLoader(transform);
    std::string objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\ground.obj)";
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = whiteLambert;
        tracer.addShape(shape);
    }

    transform = Transform::Identity();
    objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
    loader.setTransform(transform);
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes) {
        shape->shader = redLambert;
        tracer.addShape(shape);
    }

//
//    Shape *sphere1 = new Sphere(transform, 1, redLambert);
//    tracer.addShape(sphere1);

    // Initialization
    tracer.initialize();

    // Tracing the scene
    Camera cam;
    tracer.trace(cam);

    return (EXIT_SUCCESS);
}


//int main() {
//    Matrix4 mat(0.8967334, 0.4425711, 0, 0,
//                -0.4425711, 0.8967334, 0, 0,
//                0, 0, 1, 0,
//                20, -12, 7.6, 1);
//
//    Matrix4 other(1, 0, 0, 0,
//                  0, 0, -1, 0,
//                  0, 1, 0, 0,
//                  0, 0, 0, 1);
//
//    Transform trans(mat, mat.getInversed());
//    trans.rotate(Axis::x, degToRad(90));
//

//    for (int i=0 ; i < 4 ; i++)
//        for (int j=0 ; j < 4 ; j++)
//            m[i][j] = int(float(rand()) / RAND_MAX * 10);
//
//    for (int i=0 ; i < 4 ; i++) {
//        for (int j = 0; j < 4; j++)
//            std::cout << trans.matrix.m[i][j] << " ";
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl << "DET" << std::endl;
//
//    std::cout << matrixDeterminant(m, 4) << std::endl;
//
//    std::cout << std::endl << "COF" << std::endl;

//    float **cof = createMatrix(4);
//    cofactorMatrix(m, cof, 4);
//
//    for (int i=0 ; i < 4 ; i++) {
//        for (int j=0 ; j < 4 ; j++) {
//            std::cout << cof[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl << "TRANS" << std::endl;
//
//    float **trans = createMatrix(4);
//    transposeMatrix(cof, trans, 4);
//
//    for (int i=0 ; i < 4 ; i++) {
//        for (int j=0 ; j < 4 ; j++) {
//            std::cout << trans[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl << "ADJ" << std::endl;
//
//    float **adj = createMatrix(4);
//    adjugateMatrix(m, adj, 4);
//
//    for (int i=0 ; i < 4 ; i++) {
//        for (int j=0 ; j < 4 ; j++) {
//            std::cout << adj[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    std::cout << std::endl << "INV" << std::endl;
//
//    float **inv = createMatrix(4);
//    inverseMatrix(m, inv, 4);
//
//    for (int i=0 ; i < 4 ; i++) {
//        for (int j=0 ; j < 4 ; j++) {
//            std::cout << inv[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    Matrix4 mat(1, 0, 0, 0,
//                0, 1, 0, 0,
//                0, 0, 1, 0,
//                3, 2, -5, 1);
//    std::cout << "test" << std::endl;
//    Transform trans(mat, mat.getInversed());
//
//    vector3 vec(1, 5, -4);
//
//    std::cout << vec << std::endl;
//    vec*= mat;
//    std::cout << vec << std::endl;
//    std::cout << vec * trans.inverseMatrix << std::endl;
//}
