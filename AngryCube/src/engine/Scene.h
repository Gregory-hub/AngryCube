#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"
#include "engine/render/MeshBuffer.h"


class Scene
{
private:
	MeshBuffer meshBuffer;

public:
	Scene() = default;
	~Scene() = default;

    // not copyable because MeshBuffer is not copyable
	Scene(const Scene& other) = delete;
	Scene& operator= (const Scene& other) = delete;

	Scene(Scene&& other) noexcept = default;
	Scene& operator= (Scene&& other) noexcept = default;

	std::vector<std::shared_ptr<Mesh>> GetMeshes() const;

	void BindBuffer() const;
	void UnbindBuffer() const;

	void AddMesh(std::shared_ptr<Mesh>& mesh);
	void RemoveMesh(const std::shared_ptr<Mesh>& mesh);
	bool Contains(const std::shared_ptr<Mesh>& mesh) const;

	void SendMeshesToGPU();

	unsigned int GetVertexCount() const;
	unsigned int GetIndexCount() const;

	void Update(float deltaTime);
};

