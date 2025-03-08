#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "vertexarray.hpp"
#include "indexbuffer.hpp"
#include "shader.hpp"

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};