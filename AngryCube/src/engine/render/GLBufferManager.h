#pragma once
#include <vector>


class GLBufferManager
{
private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    int attributeIndex = 0;
    int attributeOffset = 0;

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

    void AddVertexAttribute(int numComponents);
    void SetVertexAttributes(const std::vector<int>& components);
    void ClearVertexAttributes();

    void SetElementBuffer(int size, const unsigned int* indices);

    void SetVertexBuffer(int size, const void* vertices);
    void UpdateVertexBuffer(int offset, int size, const void* vertices);
};

