#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "engine/components/GameObjectComponent.h"
#include "engine/render/GLBufferManager.h"
#include "engine/material/Material.h"
#include "engine/render/Shader.h"


class Mesh : public GameObjectComponent
{
protected:
    std::vector<glm::vec2> vertices;
    std::vector<glm::uvec3> triangles;
	std::unique_ptr<GLBufferManager> bufferManager;
    std::shared_ptr<Material> material;
    std::shared_ptr<Shader> shader;

public:
    Mesh();
    ~Mesh() override = default;

    Mesh(const Mesh& other);
    Mesh& operator= (Mesh other);

    Mesh(Mesh&& other) noexcept;
    Mesh& operator= (Mesh&& other) noexcept;

    std::shared_ptr<GameObjectComponent> Clone() const override;
    std::shared_ptr<GameObjectComponent> MoveClone() override;

    static void swap(Mesh& first, Mesh& second) noexcept;

    std::vector<glm::vec2> GetVertices() const;
    virtual void SetVertices(const std::vector<glm::vec2>& newVertices);

    std::vector<glm::uvec3> GetTriangles() const;
    virtual void SetTriangles(const std::vector<glm::uvec3>& newTriangles);

    const std::shared_ptr<Material>& GetMaterial() const;
    virtual void SetMaterial(const std::shared_ptr<Material>& newMaterial);

    const std::shared_ptr<Shader>& GetShader() const;

    void BindBuffers() const;
    void UnbindBuffers() const;

    unsigned int GetVertexCount() const;
    unsigned int GetIndexCount() const;

    void UpdateBuffers() const;
};

