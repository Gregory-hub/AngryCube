#include "Mesh.h"

#include "engine/utility/Logger.h"


Mesh::Mesh()
{
	prevTransform = transform;
}

std::string Mesh::GetName() const
{
	return name;
}

bool Mesh::TransformHasChanged() const
{
	return transform != prevTransform;
}

unsigned int Mesh::GetVertexCount() const
{
    return vertices.size();
}

unsigned int Mesh::GetIndexCount() const
{
    return triangles.size() * 3;
}

void Mesh::Move(const glm::vec3& value)
{
	transform.SetTranslation(transform.GetTranslation() + value);
}

void Mesh::Rotate(const float value)
{
    transform.SetRotation(transform.GetRotation() + value);
}

void Mesh::Scale(const glm::vec3& value)
{
	transform.SetScale(transform.GetScale() + value);
}

void Mesh::PostUpdate()
{
    prevTransform = transform;
}

std::vector<glm::vec4> Mesh::GetVertices() const
{
	glm::mat4 transform = GetTransformMatrix();
	std::vector<glm::vec4> result;
	result.reserve(vertices.size());
	for (glm::vec2 vertex : vertices)
		result.push_back(transform * glm::vec4(vertex, 0.0f, 1.0f));
	return result;
}

std::vector<glm::uvec3> Mesh::GetTriangles() const
{
	return triangles;
}

glm::mat4 Mesh::GetTransformMatrix() const
{
	return transform.GetMatrix();
}

