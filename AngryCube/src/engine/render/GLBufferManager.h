#pragma once

#include <GL/glew.h>


class GLBufferManager
{
private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int attributeIndex = 0;
    unsigned int attributeOffset = 0;

public:
    GLBufferManager();
    ~GLBufferManager();

    // not copyable because holds unique resources
    GLBufferManager(const GLBufferManager& other) = delete;
    GLBufferManager& operator= (const GLBufferManager& other) = delete;

    GLBufferManager(GLBufferManager&& other) noexcept;
    GLBufferManager& operator= (GLBufferManager&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void AddVertexAttribute(unsigned int numComponents);

    void SetElementBuffer(unsigned int size, unsigned int* indices);

    void SetVertexBuffer(unsigned int size, void* vertices);
    void UpdateVertexBuffer(unsigned int offset, unsigned int size, void* vertices);
};

