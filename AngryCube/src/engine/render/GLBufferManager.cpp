#include "GLBufferManager.h"

#include <utility>


GLBufferManager::GLBufferManager()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

GLBufferManager::~GLBufferManager()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

GLBufferManager::GLBufferManager(GLBufferManager&& other) noexcept
{
	vao = std::exchange(other.vao, 0);
	vbo = std::exchange(other.vbo, 0);
	ebo = std::exchange(other.ebo, 0);
	attributeIndex = std::exchange(other.attributeIndex, 0);
	attributeOffset = std::exchange(other.attributeOffset, 0);
}

GLBufferManager& GLBufferManager::operator=(GLBufferManager&& other) noexcept
{
    if (this != &other)
    {
        vao = std::exchange(other.vao, 0);
        vbo = std::exchange(other.vbo, 0);
        ebo = std::exchange(other.ebo, 0);
        attributeIndex = std::exchange(other.attributeIndex, 0);
        attributeOffset = std::exchange(other.attributeOffset, 0);
    }
    return *this;
}

void GLBufferManager::Bind() const
{
    glBindVertexArray(vao);
}

void GLBufferManager::Unbind() const
{
    glBindVertexArray(0);
}

void GLBufferManager::AddVertexAttribute(unsigned int numComponents)
{
    glEnableVertexAttribArray(attributeIndex);
    glVertexAttribPointer(attributeIndex, numComponents, GL_FLOAT, GL_FALSE, 0, (void*)attributeOffset);
    attributeIndex++;
    attributeOffset += numComponents * sizeof(float);
}

void GLBufferManager::SetElementBuffer(unsigned int size, unsigned int* indices)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void GLBufferManager::SetVertexBuffer(unsigned int size, void* vertices)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void GLBufferManager::UpdateVertexBuffer(unsigned int offset, unsigned int size, void* vertices)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
}

