#include "vertexbufferlayout.hpp"

// primary template - called when no specified type is used

template<typename T>
void VertexBufferLayout::Push(unsigned int count) {
	static_assert(false);
}

// specialized templates

template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
	m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
	m_Stride += count * VertexBufferElement::SizeOfType(GL_FLOAT);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
	m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
	m_Stride += count * VertexBufferElement::SizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
	m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
	m_Stride += count * VertexBufferElement::SizeOfType(GL_UNSIGNED_BYTE);
}