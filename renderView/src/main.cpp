#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

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

    GLFWwindow *window;
    window = glfwCreateWindow(1200, 600, "Bounce Render View", nullptr, nullptr);
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

    // Main window loop
    do{
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwWindowShouldClose(window) == 0);

}
