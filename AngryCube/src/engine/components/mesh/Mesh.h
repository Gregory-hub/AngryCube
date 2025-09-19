#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "engine/components/GameObjectComponent.h"
#include "engine/render/GLBufferManager.h"


class Mesh : public GameObjectComponent
{
protected:
    std::vector<glm::vec2> vertices;
    std::vector<glm::uvec3> triangles;
	std::unique_ptr<GLBufferManager> bufferManager;

public:
    Mesh();
    ~Mesh() override = default;

    Mesh(const Mesh& other);
    Mesh& operator= (const Mesh& other);

    Mesh(Mesh&& other) noexcept;
    Mesh& operator= (Mesh&& other) noexcept;

    std::vector<glm::vec2> GetVertices() const;
    virtual void SetVertices(const std::vector<glm::vec2>& newVertices);

    std::vector<glm::uvec3> GetTriangles() const;
    virtual void SetTriangles(const std::vector<glm::uvec3>& newTriangles);

    void BindBuffers() const;
    void UnbindBuffers() const;

    unsigned int GetVertexCount() const;
    unsigned int GetIndexCount() const;

    void UpdateBuffers() const;
};

