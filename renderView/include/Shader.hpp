//
// Created by Thomas Vallentin on 30/07/2020.
// Copyright (c) 2020. All rights reserved.
//

#ifndef BOUNCERENDERER_SHADER_HPP
#define BOUNCERENDERER_SHADER_HPP

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
public:
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    void use();

    GLuint programID;
};


#endif //BOUNCERENDERER_SHADER_HPP
