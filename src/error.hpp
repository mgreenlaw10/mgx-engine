#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <Gl/glew.h>

#include <iostream>
#include <signal.h>

/***************************************************************************************/

// for quickly adding arbitrary debug print statements
#define PRINTHI std::cout << "hi" << std::endl;

static void LookForDebugClues() {
    GLint _vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &_vao);

    if (_vao == 0) {
        std::cout << "CLUE: NO VAO BOUND" << std::endl;
    }
}

/***************************************************************************************/

#define ASSERT(x) if (!(x)) raise(SIGABRT);

#define GLCall(x)\
    GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* funcName, const char* fileName, const int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[FATAL OPENGL ERROR]" << '\n';
        std::cout << "Function: " << funcName << " in " << fileName << '\n';
        std::cout << "Line: " << line << '\n';
        std::cout << "GL Error code: " << error << '\n';

        std::cout << "\nlooking for clues..." << std::endl;
        LookForDebugClues();
        return false;
    }
    return true;
}

/***************************************************************************************/

enum ErrorType {
    GLFW_INIT_FAIL,
    GLEW_INIT_FAIL,
    WINDOW_INIT_FAIL
};

static void ExitWithError(ErrorType type) {
    switch (type) {
        case GLFW_INIT_FAIL:
            std::cerr << "GLFW FAILED TO INIT." << std::endl;
        case GLEW_INIT_FAIL:
            std::cerr << "GLEW FAILED TO INIT." << std::endl;
        case WINDOW_INIT_FAIL:
            std::cerr << "WINDOW CREATION FAILED." << std::endl;
    }
    ASSERT(false);
}

/***************************************************************************************/

static void PrintGLVersion() { 
    std::cout << glGetString(GL_VERSION) << std::endl; 
}