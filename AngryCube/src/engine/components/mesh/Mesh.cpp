#include "Mesh.h"

#include <glm/gtc/type_ptr.inl>

#include "engine/utility/Logger.h"


Mesh::Mesh()
	: bufferManager(std::make_unique<GLBufferManager>())
{
}

Mesh::Mesh(const Mesh& other)
{
	vertices = other.vertices;
	triangles = other.triangles;
	bufferManager = std::make_unique<GLBufferManager>();
	UpdateBuffers();
}

Mesh& Mesh::operator=(const Mesh& other)
{
	if (this != &other)
	{
		vertices = other.vertices;
		triangles = other.triangles;
		bufferManager = std::make_unique<GLBufferManager>();
		UpdateBuffers();
	}
	return *this;
}

Mesh::Mesh(Mesh&& other) noexcept
{
	vertices = std::exchange(other.vertices, std::vector<glm::vec2>());
	triangles = std::exchange(other.triangles, std::vector<glm::uvec3>());
	bufferManager = std::exchange(other.bufferManager, nullptr);
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this != &other)
	{
		vertices = std::exchange(other.vertices, std::vector<glm::vec2>());
		triangles = std::exchange(other.triangles, std::vector<glm::uvec3>());
		bufferManager = std::exchange(other.bufferManager, nullptr);
	}
	return *this;
}

std::vector<glm::vec2> Mesh::GetVertices() const
{
	return vertices;
}

void Mesh::SetVertices(const std::vector<glm::vec2>& newVertices)
{
	vertices = newVertices;
}

std::vector<glm::uvec3> Mesh::GetTriangles() const
{
	return triangles;
}

void Mesh::SetTriangles(const std::vector<glm::uvec3>& newTriangles)
{
	triangles = newTriangles;
}

void Mesh::BindBuffers() const
{
	bufferManager->Bind();
}

void Mesh::UnbindBuffers() const
{
	bufferManager->Unbind();
}

unsigned int Mesh::GetVertexCount() const
{
    return vertices.size();
}

unsigned int Mesh::GetIndexCount() const
{
    return triangles.size() * 3;
}

void Mesh::UpdateBuffers() const
{
	bufferManager->SetVertexBuffer(vertices.size() * sizeof(glm::vec2), vertices.empty() ? nullptr : glm::value_ptr(vertices[0]));
	bufferManager->SetElementBuffer(GetIndexCount() * sizeof(glm::uvec3), triangles.empty() ? nullptr : glm::value_ptr(triangles[0]));
	bufferManager->SetVertexAttributes({ 2 });
}

