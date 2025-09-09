#include "Transform.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
 

glm::vec3 Transform::GetTranslation() const
{
	return translation;
}

float Transform::GetRotation() const
{
	return rotation;
}

glm::vec3 Transform::GetScale() const
{
	return scale;
}

void Transform::SetTranslation(const glm::vec3& value)
{
	translation = value;
}

void Transform::SetRotation(const float value)
{
	rotation = value;
}

void Transform::SetScale(const glm::vec3& value)
{
	scale = value;
}

glm::mat4 Transform::GetMatrix() const
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, translation);
	transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
	transform = glm::scale(transform, scale);
    return transform;
}

bool Transform::operator==(const Transform& other)
{
	return *const_cast<const Transform*>(this) == other;
}

bool Transform::operator==(const Transform& other) const
{
	return (translation == other.translation) && (rotation == other.rotation) && (scale == other.scale);
}

void Transform::ShowDebugControls()
{
    ImGui::DragFloat3("Translation", &translation.x);
    ImGui::DragFloat("Rotation", &rotation);
    ImGui::DragFloat3("Scale", &scale.x, 0.01f);
}

