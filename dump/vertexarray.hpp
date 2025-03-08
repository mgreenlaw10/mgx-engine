#pragma once

#include "vertexbuffer.hpp"
#include "vertexbufferlayout.hpp"

class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};