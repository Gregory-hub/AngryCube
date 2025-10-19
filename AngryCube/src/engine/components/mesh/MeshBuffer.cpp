#include "pch.h"
#include "MeshBuffer.h"

#include <vector>
#include <utility>

#include <glm/glm.hpp>

#include "engine/utility/Logger.h"


MeshBuffer::MeshBuffer()
	: bufferManager(std::make_unique<GLBufferManager>())
{
}

MeshBuffer::~MeshBuffer()
{
}

MeshBuffer::MeshBuffer(MeshBuffer&& other) noexcept
{
	bufferManager = std::exchange(other.bufferManager, nullptr);
	meshOffsets = std::move(other.meshOffsets);
	meshVertexCount = std::exchange(other.meshVertexCount, 0);
	vertexCount = std::exchange(other.vertexCount, 0);
	indexCount = std::exchange(other.indexCount, 0);
}

MeshBuffer& MeshBuffer::operator=(MeshBuffer&& other) noexcept
{
	if (this != &other)
	{
		bufferManager = std::exchange(other.bufferManager, nullptr);
		meshOffsets = std::move(other.meshOffsets);
		meshVertexCount = std::exchange(other.meshVertexCount, 0);
		vertexCount = std::exchange(other.vertexCount, 0);
		indexCount = std::exchange(other.indexCount, 0);
	}
	return *this;
}

unsigned int MeshBuffer::GetVertexCount() const
{
	return vertexCount;
}

unsigned int MeshBuffer::GetIndexCount() const
{
	return indexCount;
}

std::vector<std::shared_ptr<Mesh>> MeshBuffer::GetMeshes() const
{
	std::vector<std::shared_ptr<Mesh>> meshes;
	meshes.reserve(meshOffsets.size());
	for (const auto& [mesh, _] : meshOffsets)
		meshes.push_back(mesh);
	return meshes;
}

bool MeshBuffer::Contains(const std::shared_ptr<Mesh>& mesh) const
{
	return meshOffsets.contains(mesh);
}

void MeshBuffer::AddMesh(std::shared_ptr<Mesh>& mesh)
{
	if (!meshOffsets.contains(mesh))
	{
		meshOffsets[mesh] = -1;
		vertexCount += mesh->GetVertexCount();
		indexCount += mesh->GetIndexCount();
	}
}

void MeshBuffer::RemoveMesh(const std::shared_ptr<Mesh>& mesh)
{
	if (meshOffsets.contains(mesh))
	{
		meshOffsets.erase(mesh);
		vertexCount -= mesh->GetVertexCount();
		indexCount -= mesh->GetIndexCount();
	}
}

void MeshBuffer::Bind() const
{
	bufferManager->Bind();
}

void MeshBuffer::Unbind() const
{
	bufferManager->Unbind();
}

void MeshBuffer::SetBufferOnGPU()
{
	std::vector<glm::vec2> vertices(vertexCount);
	std::vector<unsigned int> indices;
	indices.reserve(indexCount);

	unsigned int offset = 0;
	for (const auto& [mesh, _] : meshOffsets)
	{
		std::vector<glm::vec2> meshVertices = mesh->GetVertices();
		std::copy(meshVertices.begin(), meshVertices.end(), vertices.begin() + offset);

		for (glm::uvec3 triangle : mesh->GetTriangles())
		{
			indices.push_back(triangle.x + offset);
			indices.push_back(triangle.y + offset);
			indices.push_back(triangle.z + offset);
		}

		meshOffsets[mesh] = offset * sizeof(glm::vec2);

		if (offset == 0)
			meshVertexCount = mesh->GetVertexCount();
		offset += meshVertexCount;
	}

	//Logger::Log(LogLevel::Info, "Buffers are being allocated on gpu");

	bufferManager->SetVertexBuffer(vertexCount * sizeof(glm::vec2), vertices.data());
	bufferManager->SetElementBuffer(indexCount * sizeof(unsigned int), indices.data());
	bufferManager->AddVertexAttribute(2);
}

void MeshBuffer::UpdateMeshOnGPU(const std::shared_ptr<Mesh>& mesh)
{
	//Logger::Log(LogLevel::Info, std::string("Mesh ") + mesh->GetName() + " is being updated on gpu");

	std::vector<glm::vec2> meshVertices = mesh->GetVertices();
	if (meshOffsets.contains(mesh))
		bufferManager->UpdateVertexBuffer(meshOffsets[mesh], meshVertexCount * sizeof(glm::vec2), meshVertices.data());
	else
		Logger::Log(LogLevel::Warning, "UpdateBuffer: mesh is not in buffer");
}

