// Bounce render view
#include "GLShader.hpp"

// Bounce renderer
#include "core/RayTracer.hpp"
#include "accelerators/BVH.hpp"
#include "loaders/OBJLoader.hpp"
#include "adapters/PPMAdapter.hpp"
#include "samplers/RandomSampler.hpp"
#include "samplers/HierarchicalAdaptive.hpp"
#include "shapes/Sphere.h"
#include "shapes/TriangleMesh.hpp"
#include "lights/PointLight.hpp"
#include "lights/GradientLight.hpp"

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// std lib
#include <random>
#include <iostream>
#include <algorithm>
#include <thread>

void windowSizeChanged(GLFWwindow *window, int winWidth, int winHeight);

static RayTracer tracer(0.001, 100000, 16, 100);
static Scene scene;
void traceRender();
void initializeTracer();
void fillScene();

void extractTracedImage(float *data);
void updateTextureFromRender(GLuint texture, float *data);

static int initialWidth(1200), initialHeight(600);
static int renderWidth(500), renderHeight(500);
static int samples(32);

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

    glfwSetWindowPos(window, 200, 200);

    // Setting up callbacks
    glfwSetWindowSizeCallback(window, windowSizeChanged);

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

    // Starting renderThread
    std::thread renderThread(traceRender);

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

    renderThread.join();

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
    if (!tracer.isInitialized())
        return;
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
        {
            data[(renderHeight - 1 - i) * renderWidth * 3 + j] = applyGamma(tracer.pixels()[i*renderWidth * 3 + j], tracer.gamma());
        }
}

void traceRender()
{
    std::cout << "fillScene "  << std::endl;
    fillScene();

    std::cout << "initialize "  << std::endl;
    tracer.initialize(&scene);
    std::cout << "trace "  << std::endl;
    tracer.trace();
}

void fillScene() {
    std::cout << "Hello, welcome to Bounce Renderer !" << std::endl;

    Accelerator *accelerator = new BVH;
    scene.accelerator = accelerator;

    Shader *mirror = new Metal(.0, .0, .0, .05);
    Shader *greySurface = new SurfaceShader(.2, .2, .2, .05);
    Shader *whiteLambert = new Lambert(.5, .5, .5);
    Shader *redLambert = new Lambert(.8, 0.05, 0.05);
    Shader *greenLambert = new Lambert(0.1, 0.9, 0.1);
    Shader *blueLambert = new Lambert(0.1, 0.1, 0.9);
    Shader *yellowLambert = new Lambert(.9f, .6f, 0.2);

    OBJLoader *loader = new OBJLoader();

    // Loading the ground
    // Loading the ground
    Transform *transform = Transform::Identity();
    transform->scale(100, 100, 100);
    transform->translate(280, -50, -500);
    loader->setTransform(transform);
    loader->load(R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\bunny.obj)", false);

    for (Shape *shape : loader->shapes) {
        shape->shader = whiteLambert;
        scene.addShape(shape);
    }

    // Loading the ground
    transform = Transform::Identity();
    transform->scale(100, 100, 100);
    transform->translate(280, -50, -500);
    loader->setTransform(transform);
    loader->load(R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\ground.obj)", false);

    for (Shape *shape : loader->shapes) {
        shape->shader = whiteLambert;
        scene.addShape(shape);
    }

    GradientLight *gLight = new GradientLight();
    gLight->intensity = 0.1f;
    scene.addLight(gLight);

    transform = Transform::Identity();
    transform->rotate(Axis::x, degToRad(-20));
    transform->rotate(Axis::y, degToRad(60));
    transform->translate(-100, 200, -500);
    PointLight *pLight = new PointLight(transform, Color(1.0f, 1.0f, 1.0f), 60000.0f);
    scene.addLight(pLight);

    // Camera
    Vector3 from(211, 150, 390), to(211, 100, -500);
    transform = Transform::LookAt(from, to, true);

    Camera cam(transform, 35, FilmGate::Film35mm);
    cam.focusDistance = 1300;
    cam.apertureRadius = 0.0f;
    cam.setResolution(renderWidth, renderHeight);

    tracer.setCamera(cam);
    tracer.setOutpath(R"(D:\REPO\Bounce\bounceRenderer\output\output.ppm)");
    tracer.setAdapter(new PPMAdapter());
    tracer.setSampler(new HierarchicalAdaptive(0.0001));

}
