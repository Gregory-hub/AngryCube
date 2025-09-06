#include "Model.h"


unsigned int Model::GetVertexCount() const
{
    return vertices.size();
}

unsigned int Model::GetIndexCount() const
{
    return indices.size() * 3;
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

