#include "Transform.h"

#include <memory>

#include <imgui.h>

#include "engine/world/GameObject.h"


Transform::Transform(GameObject* parentObject)
	: GameObjectComponent(parentObject)
{
}

glm::vec2 Transform::GetTranslation() const
{
	return translation;
}

float Transform::GetRotation() const
{
	return rotation;
}

glm::vec2 Transform::GetScale() const
{
	return scale;
}

void Transform::SetTranslation(const glm::vec2& value)
{
	translation = value;
}

void Transform::SetRotation(float value)
{
	rotation = value;
}

void Transform::SetScale(const glm::vec2& value)
{
	scale = value;
}

void Transform::Move(const glm::vec2& value)
{
    SetTranslation(translation + value);
}

void Transform::Rotate(float value)
{
    SetRotation(rotation + value);
}

void Transform::Scale(const glm::vec2& value)
{
	SetScale(scale + value);
}

glm::mat4 Transform::GetMatrix() const
{
	glm::mat4 transform(1.0f);

	GameObject* parent = parentObject->GetParent();
	while (parent)
	{
		transform = glm::translate(transform, glm::vec3(parent->GetTransform().GetTranslation(), 0.0f));
		transform = glm::rotate(transform, glm::radians(parent->GetTransform().GetRotation()), { 0.0f, 0.0f, 1.0f });
		parent = parent->GetParent();
	}

	transform = glm::translate(transform, glm::vec3(translation, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
	transform = glm::scale(transform, glm::vec3(scale, 0.0f));

    return transform;
}

bool Transform::operator==(const Transform& other)
{
	return *const_cast<const Transform*>(this) == other;
}

bool Transform::operator==(const Transform& other) const
{
	return (translation == other.translation) && (abs(rotation - other.rotation) < 10e-6) && (scale == other.scale);
}

void Transform::ShowDebugControls()
{
    ImGui::DragFloat2("Translation", &translation.x);
    ImGui::DragFloat("Rotation", &rotation);
    ImGui::DragFloat2("Scale", &scale.x, 0.01f);
}

