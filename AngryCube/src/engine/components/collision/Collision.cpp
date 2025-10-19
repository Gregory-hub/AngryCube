#include "pch.h"
#include "Collision.h"

#include <glm/glm.hpp>

#include "engine/world/GameObject.h"


Collision::Collision(GameObject* parentObject)
	: GameObjectComponent(parentObject)
{
}

void Collision::Enable()
{
	enabled = true;
}

void Collision::Disable()
{
	enabled = false;
}

bool Collision::Enabled() const
{
	return enabled;
}

bool Collision::IsColliding(const std::shared_ptr<GameObject>& other) const
{
	if (!enabled || !parentObject->GetCollisionMesh() || !other->GetCollisionMesh())
		return false;

	glm::vec2 thisLocation = parentObject->GetTransform().GetTranslation();
	float thisHalfWidth = parentObject->GetCollisionMesh()->GetWidth()  / 2.0f;
	float thisHalfHeight = parentObject->GetCollisionMesh()->GetHeight() / 2.0f;

	glm::vec2 otherLocation = other->GetTransform().GetTranslation();
	float otherHalfWidth = other->GetCollisionMesh()->GetWidth()  / 2.0f;
	float otherHalfHeight = other->GetCollisionMesh()->GetHeight() / 2.0f;

	glm::vec2 distance = otherLocation - thisLocation;
	if (abs(distance.x) <= thisHalfWidth + otherHalfWidth && abs(distance.y) <= thisHalfHeight + otherHalfHeight)
		return true;
	else
		return false;
}

