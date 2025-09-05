#include "Model.h"

#include <GL/glew.h>


void Model::Bind() const
{
    glBindVertexArray(vao);
}

void Model::Unbind() const
{
    glBindVertexArray(0);
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

glm::mat4 Model::GetTransformMatrix() const
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
	transform = glm::scale(transform, scale);
    return transform;
}

