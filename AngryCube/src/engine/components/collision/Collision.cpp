#include "Collision.h"

#include "engine/world/GameObject.h"


Collision::Collision(GameObject* parentObject)
	: parentObject(parentObject)
{
}

bool Collision::IsColliding(const std::shared_ptr<GameObject>& other) const
{
	glm::vec2 thisLocation = parentObject->GetTransform().GetTranslation();
	float thisHalfWidth = parentObject->GetWidth()  / 2.0f;
	float thisHalfHeight = parentObject->GetHeight() / 2.0f;

	glm::vec2 otherLocation = other->GetTransform().GetTranslation();
	float otherHalfWidth = other->GetWidth()  / 2.0f;
	float otherHalfHeight = other->GetHeight() / 2.0f;

	glm::vec2 distance = otherLocation - thisLocation;
	if (abs(distance.x) <= thisHalfWidth + otherHalfWidth && abs(distance.y) <= thisHalfHeight + otherHalfHeight)
		return true;
	else
		return false;
}

