#include "Model.h"


unsigned int Model::GetVertexCount() const
{
    return vertices.size();
}

unsigned int Model::GetIndexCount() const
{
    return triangles.size() * 3;
}

glm::vec3 Model::GetTranslation() const
{
	return translation;
}

float Model::GetRotation() const
{
	return rotation;
}

glm::vec3 Model::GetScale() const
{
	return scale;
}

void Model::SetTranslation(const glm::vec3& value)
{
	translation = value;
}

void Model::SetRotation(const float value)
{
	rotation = value;
}

void Model::SetScale(const glm::vec3& value)
{
	scale = value;
}

void Model::Move(const glm::vec3& value)
{
	translation += value;
}

void Model::Rotate(const float value)
{
    rotation += value;
}

void Model::Scale(const glm::vec3& value)
{
    scale += value;
}

std::vector<glm::vec4> Model::GetVertices() const
{
	glm::mat4 transform = GetTransformMatrix();
	std::vector<glm::vec4> result;
	result.reserve(vertices.size());
	for (glm::vec2 vertex : vertices)
		result.push_back(transform * glm::vec4(vertex, 0.0f, 1.0f));
	return result;
}

std::vector<glm::uvec3> Model::GetTriangles() const
{
	return triangles;
}

glm::mat4 Model::GetTransformMatrix() const
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
	transform = glm::scale(transform, scale);
    return transform;
}

