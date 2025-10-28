#include "pch.h"
#include "Mesh.h"


Mesh::Mesh()
	: GameObjectComponent(nullptr), bufferManager(std::make_unique<GLBufferManager>())
{
}

Mesh::Mesh(const Mesh& other)
	: Mesh()
{
	vertices = other.vertices;
	triangles = other.triangles;
	material = other.material;
	shader = other.shader;
	
	UpdateBuffers();
}

Mesh& Mesh::operator=(Mesh other)
{
	swap(*this, other);
	UpdateBuffers();
	return *this;
}

Mesh::Mesh(Mesh&& other) noexcept
	: GameObjectComponent(std::move(other)),
	vertices(std::move(other.vertices)),
	triangles(std::exchange(other.triangles, std::vector<glm::uvec3>())),
	bufferManager(std::exchange(other.bufferManager, nullptr)),
	material(std::move(other.material)),
	shader(std::move(other.shader))
{
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	Mesh tmp(std::move(other));
	swap(*this, tmp);
	return *this;
}

std::shared_ptr<GameObjectComponent> Mesh::Clone() const
{
	return std::make_shared<Mesh>(*this);
}

std::shared_ptr<GameObjectComponent> Mesh::MoveClone()
{
	return std::make_shared<Mesh>(std::move(*this));
}

void Mesh::swap(Mesh& first, Mesh& second) noexcept
{
	std::swap(first.vertices, second.vertices);
	std::swap(first.triangles, first.triangles);
	std::swap(first.bufferManager, first.bufferManager);
	std::swap(first.material, first.material);
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

const std::shared_ptr<Material>& Mesh::GetMaterial() const
{
	return material;
}

void Mesh::SetMaterial(const std::shared_ptr<Material>& newMaterial)
{
	material = newMaterial;
}

const std::shared_ptr<Shader>& Mesh::GetShader() const
{
	return shader;
}

void Mesh::BindBuffers() const
{
	bufferManager->Bind();
}

void Mesh::UnbindBuffers() const
{
	bufferManager->Unbind();
}

int Mesh::GetVertexCount() const
{
    return vertices.size();
}

int Mesh::GetIndexCount() const
{
    return triangles.size() * 3;
}

void Mesh::UpdateBuffers() const
{
	bufferManager->SetVertexBuffer(vertices.size() * sizeof(glm::vec2), vertices.empty() ? nullptr : glm::value_ptr(vertices[0]));
	bufferManager->SetElementBuffer(GetIndexCount() * sizeof(glm::uvec3), triangles.empty() ? nullptr : glm::value_ptr(triangles[0]));
	bufferManager->SetVertexAttributes({ 2 });
}
