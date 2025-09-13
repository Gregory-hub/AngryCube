#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "engine/render/GLBufferManager.h"


class Mesh
{
protected:
    std::vector<glm::vec2> vertices;
    std::vector<glm::uvec3> triangles;
	std::unique_ptr<GLBufferManager> bufferManager;

public:
    Mesh();
    ~Mesh() = default;

    Mesh(const Mesh& other);
    Mesh& operator= (const Mesh& other);

    Mesh(Mesh&& other) noexcept;
    Mesh& operator= (Mesh&& other) noexcept;

    std::vector<glm::vec2> GetVertices() const;
    void SetVertices(const std::vector<glm::vec2>& newVertices);

    std::vector<glm::uvec3> GetTriangles() const;
    void SetTriangles(const std::vector<glm::uvec3>& newTriangles);

    void BindBuffers() const;
    void UnbindBuffers() const;

    unsigned int GetVertexCount() const;
    unsigned int GetIndexCount() const;

    void UpdateBuffers() const;
};

