#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "engine/components/mesh/Mesh.h"
#include "engine/render/GLBufferManager.h"


// for rendering many meshes in a single draw call
class MeshBuffer
{
private:
	std::unique_ptr<GLBufferManager> bufferManager;
	std::unordered_map<std::shared_ptr<Mesh>, int> meshOffsets;
	int meshVertexCount = 0;
	int vertexCount = 0;
	int indexCount = 0;

public:
	MeshBuffer();
	~MeshBuffer();

    // not copyable because GLBufferManager is not copyable
	MeshBuffer(const MeshBuffer& other) = delete;
	MeshBuffer& operator= (const MeshBuffer& other) = delete;

	MeshBuffer(MeshBuffer&& other) noexcept;
	MeshBuffer& operator= (MeshBuffer&& other) noexcept;

	int GetVertexCount() const;
	int GetIndexCount() const;

	std::vector<std::shared_ptr<Mesh>> GetMeshes() const;
	bool Contains(const std::shared_ptr<Mesh>& mesh) const;
	void AddMesh(std::shared_ptr<Mesh>& mesh);
	void RemoveMesh(const std::shared_ptr<Mesh>& mesh);

	void Bind() const;
	void Unbind() const;

	void SetBufferOnGPU();
	void UpdateMeshOnGPU(const std::shared_ptr<Mesh>& mesh);
};

