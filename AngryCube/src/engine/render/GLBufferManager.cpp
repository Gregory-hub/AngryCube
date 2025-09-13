#include "GLBufferManager.h"

#include <utility>
#include <stdexcept>

#include <GL/glew.h>


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
    if (numComponents < 1 || numComponents > 4)
        throw std::out_of_range("Number of components must be 1, 2, 3 or 4");

    Bind();
    glEnableVertexAttribArray(attributeIndex);
    glVertexAttribPointer(attributeIndex, numComponents, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(attributeOffset));
    attributeIndex++;
    attributeOffset += numComponents * sizeof(float);
}

void GLBufferManager::SetVertexAttributes(const std::vector<unsigned int>& components)
{
    ClearVertexAttributes();
    for (unsigned int num : components)
        AddVertexAttribute(num);
}

void GLBufferManager::ClearVertexAttributes()
{
    Bind();
    while (attributeIndex > 0)
        glDisableVertexAttribArray(attributeIndex--);
    attributeOffset = 0;
}

void GLBufferManager::SetElementBuffer(unsigned int size, const unsigned int* indices)
{
    Bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void GLBufferManager::SetVertexBuffer(unsigned int size, const void* vertices)
{
    Bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void GLBufferManager::UpdateVertexBuffer(unsigned int offset, unsigned int size, const void* vertices)
{
    Bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
}

