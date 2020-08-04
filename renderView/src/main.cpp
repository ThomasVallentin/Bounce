#define _WIN32_WINNT 0x0501
// Bounce renderer
#include "GLShader.hpp"
#include "RayTracer.h"
#include "TriangleMesh.hpp"
#include "FileLoaders.hpp"

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <random>
#include <iostream>
#include <algorithm>
#include "mingw.thread.h"

void windowSizeChanged(GLFWwindow *window, int winWidth, int winHeight);
//void onScroll(GLFWwindow *window, double winWidth, double winHeight);

static RayTracer tracer;
void traceRender(Camera *cam);
void initializeTracer(RayTracer &raytracer);
void fillScene();

void extractTracedImage(float *data);
void updateTextureFromRender(GLuint texture, float *data);

static int initialWidth(1200), initialHeight(600);
static int renderWidth(1280), renderHeight(720);
static int samples(100);

const int renderPixelCount(renderWidth * renderHeight * 3);
static float aspectRatio(float(renderWidth) / float(renderHeight));

static float backgroundColor[] = {0.175f, 0.175f, 0.19f, 1.0f};


int main()
{
    // == GLFW initialization ==========================================================================================

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow *window;
    window = glfwCreateWindow(initialWidth, initialHeight, "Bounce Render View", nullptr, nullptr);
    if ( window==nullptr)
    {
        std::cout << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // == GLEW initialization ==========================================================================================

    glfwMakeContextCurrent(window);
    if ( glewInit() != GLEW_OK )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // == Window initialization ==========================================================================================

    // Setting up callbacks
    glfwSetWindowSizeCallback(window, windowSizeChanged);
//    glfwSetScrollCallback(window, onScroll);

    // Resize viewport to fit window size
    windowSizeChanged(window, initialWidth, initialHeight);

    // ==  Screen =============================================================

    // Vertices positions
    const GLfloat vertices[] = {
            // positions          // uvs
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
             1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
             1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
    };
    // Vertices indices
    const GLuint verticesIndices[] = {
            0, 1, 3,
            1, 2, 3
    };

    // Texture data
    float *data;

    data = new float[renderPixelCount];


    // Generate data structures
    GLuint screenVAO, screenVBO, screenEBO;
    glGenVertexArrays(1, &screenVAO);
    glGenBuffers(1, &screenVBO);
    glGenBuffers(1, &screenEBO);

    // Working on this vertex array
    glBindVertexArray(screenVAO);

    // Copy vertices positions to vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copy vertices indices to element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesIndices), verticesIndices, GL_STATIC_DRAW);

    // Setup vertex pointer for points data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Create texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Setup vertex pointer for texture data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Some cleaning (optional)
    glBindVertexArray(0);  // unbing vertex array

    // Compile screen's shader
    GLShader screenShader("..\\shaders\\screenShader.vert", "..\\shaders\\screenShader.frag");

    // == Initialize raytracer =========================================================================================
    // Render engine initialization

    fillScene();

    initializeTracer(tracer);

    // Starting thread using render
    Camera cam;
    std::thread renderThread(traceRender, &cam);

    // Main window loop
    do {
        updateTextureFromRender(texture, data);

        glClearColor(backgroundColor[0],
                     backgroundColor[1],
                     backgroundColor[2],
                     backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);

        // Were using the previously created screen shader
        screenShader.use();

        // Drawing our triangles
        glBindVertexArray(screenVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}


void windowSizeChanged(GLFWwindow *window, int winWidth, int winHeight)
{
    // Ensure the viewport fits the window as much as possible
    float vpHeight = std::min(winWidth / aspectRatio, float(winHeight));
    float vpWidth = vpHeight * aspectRatio;
    float vpX = (winWidth - vpWidth) / 2;
    float vpY = (winHeight - vpHeight) / 2;

    glViewport(vpX, vpY, vpWidth, vpHeight);
}

void updateTextureFromRender(GLuint texture, float *data)
{
    extractTracedImage(data);

    // Fill texture with image data
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderWidth, renderHeight, 0, GL_RGB, GL_FLOAT, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void extractTracedImage(float *data)
{
    for (int i=0 ; i < renderHeight; i++)
        for (int j=0 ; j < renderWidth * 3; j++)
            data[(renderHeight - 1 - i) * renderWidth * 3 + j] = applyGamma(tracer.pixels()[i*renderWidth * 3 + j], tracer.gamma());
}

void traceRender(Camera *cam)
{
    tracer.trace(*cam);
}

void initializeTracer(RayTracer &raytracer)
{
    raytracer.setSamples(samples);
    raytracer.setWidth(renderWidth);
    raytracer.setHeight(renderHeight);
    raytracer.initialize();
}

void fillScene() {
    Shader *mirrorShader = new SurfaceShader(.8, .8, .8, .1);
    Shader *greyLambert = new Lambert(.3, .3, .3);
    Shader *redLambert = new Lambert(0.8, 0.05, 0.05);
    Shader *greenLambert = new Lambert(0.1, 0.9, 0.1);
    Shader *blueLambert = new Lambert(0.1, 0.1, 0.9);

    // Loading the ground
    Transform *transform = Transform::Identity();
    transform->translate(0, 0.04, 0);
    OBJLoader loader = OBJLoader(transform);
    std::string objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\ground.obj)";
    loader.load(objPath, false);

    for (Shape *shape : loader.shapes)
    {
        shape->shader = greyLambert;
        tracer.addShape(shape);
    }

    // Loading the test geometry
//    transform = Transform::Identity();
//    objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
//    loader.setTransform(transform);
//    loader.load(objPath, false);
//
//    for (Shape *shape : loader.shapes) {
//        shape->shader = redLambert;
//        tracer.addShape(shape);
//    }

    transform = Transform::Identity();
    transform->translate(0, 1, -7);
    Shape *sphere1 = new Sphere(transform, 1, redLambert);
    tracer.addShape(sphere1);
//
//    transform = Transform::Identity();
//    transform->translate(2, 1, -7);
//    Shape *sphere2 = new Sphere(transform, 1, greenLambert);
//    tracer.addShape(sphere2);
//
//    transform = Transform::Identity();
//    transform->translate(-2, 1, -7);
//    Shape *sphere3 = new Sphere(transform, 1, blueLambert);
//    tracer.addShape(sphere3);
}
