//
// Created by Thomas Vallentin on 30/07/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCERENDERER_GLSHADER_HPP
#define BOUNCERENDERER_GLSHADER_HPP

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class GLShader {
public:
    GLShader(const char *vertexShaderPath, const char *fragmentShaderPath);
    void use();

    GLuint programID;
};


#endif //BOUNCERENDERER_GLSHADER_HPP
