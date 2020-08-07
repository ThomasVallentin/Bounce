#include "RayTracer.h"
#include "Sphere.h"
#include "FileLoaders.hpp"

#include <iostream>

int main() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    int renderWidth = 500;
    int renderHeight = 500;
    float nearClip = 0.001;
    float farClip = 100000;
    int samples = 2;

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
        tracer.addShape(shape);
    }

    transform = Transform::Identity();
    transform->translate(0, 1, -7);
    Shape *sphere1 = new Sphere(transform, 1, redLambert);
    tracer.addShape(sphere1);

//    transform = Transform::Identity();
//    transform->translate(0, 0.01, -7);
//    objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
//    loader.setTransform(transform);
//    loader.load(objPath, false);
//
//    for (Shape *shape : loader.shapes) {
//        shape->shader = redLambert;
//        tracer.addShape(shape);
//    }

    transform = Transform::Identity();
    transform->translate(1, 1, -12);
    Shape *sphere2 = new Sphere(transform, 1, greenLambert);
    tracer.addShape(sphere2);

    transform = Transform::Identity();
    transform->translate(-1, 1, -2);
    Shape *sphere3 = new Sphere(transform, 1, blueLambert);
    tracer.addShape(sphere3);

    // Camera
    Vector3 from(0, 1.2, 11), to(0, 1.2, -7);
    transform = Transform::LookAt(from, to, true);

    Camera cam(transform, 60, FilmGate::Film35mm);
    cam.focusDistance = (to - from).length();
    cam.apertureRadius = 0.5f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);

    // Initialization
    tracer.initialize();

    // Start rendering
    tracer.trace();

    return (EXIT_SUCCESS);
}


//int main() {
//    Vector3 from(0, 5, 0);
//    Vector3 to(0, 0, 5);
//
//    Transform *trans = Transform::LookAt(from, to, true);
//    for (int i=0 ; i < 4 ; i++) {
//        for (int j = 0; j < 4; j++)
//            std::cout << trans->matrix.m[i][j] << " ";
//        std::cout << std::endl;
//
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
//    Vector3 vec(1, 5, -4);
//
//    std::cout << vec << std::endl;
//    vec*= mat;
//    std::cout << vec << std::endl;
//    std::cout << vec * trans.inverseMatrix << std::endl;
//}
