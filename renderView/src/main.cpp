#include "Shader.hpp"

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>

void windowSizeChanged(GLFWwindow *window, int winWidth, int winHeight);
//void onScroll(GLFWwindow *window, double winWidth, double winHeight);

static float aspectRatio(1.777777778f);
static int initialWidth(1200), initialHeight(600);
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
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
    };
    // Vertices indices
    const GLuint verticesIndices[] = {
            0, 1, 3,
            1, 2, 3
    };

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

    // Setup vertex pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind current vertex array (optional, just here so that everything is clean)
    glBindVertexArray(0);

    // Compile screen's shader
    Shader screenShader("..\\shaders\\screenShader.vert", "..\\shaders\\screenShader.frag");
    // Main window loop
    do {
        glClearColor(backgroundColor[0],
                     backgroundColor[1],
                     backgroundColor[2],
                     backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // Were using the previously created screen shader
        screenShader.use();

        // Drawing our triangles
        glBindVertexArray(screenVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwWindowShouldClose(window) == 0);

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
