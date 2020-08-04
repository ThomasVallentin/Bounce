//
// Created by Thomas Vallentin on 30/07/2020.
// Copyright (c) 2020. All rights reserved.
//

#include "GLShader.hpp"

GLShader::GLShader(const char *vertexShaderPath, const char *fragmentShaderPath) {

    // ==  Reading shader code  ===============================================

    std::string vertexCodeString;
    std::string fragmentCodeString;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    try {
        // Open files
        vertexFile.open(vertexShaderPath);
        fragmentFile.open(fragmentShaderPath);

        // Read files in string stream
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        // Close files
        vertexFile.close();
        fragmentFile.close();

        // Fill string with string content
        vertexCodeString = vertexStream.str();
        fragmentCodeString = fragmentStream.str();
    }
    catch (std::ifstream::failure &e) {
        std::cerr << "GLShader : Error reading file..." << std::endl;
    }

    const char *vertexCode = vertexCodeString.c_str();
    const char *fragmentCode = fragmentCodeString.c_str();

    // ==  Compiling shaders  =================================================

    GLuint vertexShader, fragmentShader;
    int success;
    char status[512];

    // Compiling vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, nullptr);
    glCompileShader(vertexShader);

    // Getting vertex compiling status
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, status);
        std::cerr << "Error compiling vertex shader:\n" << status << std::endl;
    }

    // Compiling fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentShader);

    // Getting fragment compiling status
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, status);
        std::cerr << "Error compiling fragment shader :\n" << status << std::endl;
    }

    // Create & initialize shader program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Getting program compiling status
    glGetProgramiv(programID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, nullptr, status);
        std::cerr << "Error compiling shader program :\n" << status << std::endl;
    }

    // Shaders aren't needed anymore since they are already linked inside the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GLShader::use()
{
    glUseProgram(programID);
}