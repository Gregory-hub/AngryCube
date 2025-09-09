#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "engine/Mesh.h"
#include "engine/render/GLBufferManager.h"


class MeshBuffer
{
private:
	GLBufferManager bufferManager;
	std::unordered_map<std::shared_ptr<Mesh>, unsigned int> meshOffsets;
	unsigned int meshVertexCount = -1;
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;

public:
	unsigned int GetVertexCount() const;
	unsigned int GetIndexCount() const;

	std::vector<std::shared_ptr<Mesh>> GetMeshes() const;
	bool Contains(const std::shared_ptr<Mesh>& mesh) const;
	void AddMesh(std::shared_ptr<Mesh>& mesh);
	void RemoveMesh(const std::shared_ptr<Mesh>& mesh);

	void Bind() const;
	void Unbind() const;

	void SetBufferOnGPU();
	void UpdateMeshOnGPU(const std::shared_ptr<Mesh>& mesh);
};

