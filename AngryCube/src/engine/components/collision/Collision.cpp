#include "pch.h"
#include "Collision.h"

#include <glm/glm.hpp>

#include "engine/world/GameObject.h"


Collision::Collision(GameObject* parentObject)
	: GameObjectComponent(parentObject)
{
}

std::shared_ptr<GameObjectComponent> Collision::Clone() const
{
	return std::make_shared<Collision>(*this);
}

std::shared_ptr<GameObjectComponent> Collision::MoveClone()
{
	return std::make_shared<Collision>(std::move(*this));
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

bool Collision::IsColliding(std::shared_ptr<GameObject> other) const
{
	if (!CanCollide(other))
		return false;

	glm::vec2 d = CalculateDistanceToObject(other);
	return d.x <= 0 && d.y <= 0;
}

void Collision::ResolvePenetration(std::shared_ptr<GameObject> penetrated)
{
	if (!CanCollide(penetrated))
		return;

	float vThreshold = 1e-6;

	if (!parentObject->GetPhysics().Enabled() || parentObject->GetPhysics().GetVelocity().length() < vThreshold)
		return;

	glm::vec2 d = CalculateDistanceToObject(penetrated);
	glm::vec2 v = parentObject->GetPhysics().GetVelocity();
	if (d.x < 0 && d.y < 0 && v.length() > vThreshold)
	{
		float k = 0.0f;
		if (abs(d.x) <= abs(d.y) && abs(v.x) > vThreshold)
			k = abs(d.x / v.x);
		else if (abs(d.x) > abs(d.y) && abs(v.y) > vThreshold)
			k = abs(d.y / v.y);

		glm::vec2 moveBack = -k * v;

		if (!DidHitSide(penetrated))
		{
			// Hit from up or down
			v.y = 0.0f;
			moveBack.x = 0.0f;
		}
		else
		{
			// Hit from side
			v.x = 0.0f;
			moveBack.y = 0.0f;
		}

		parentObject->GetTransform().Move(moveBack);

		parentObject->GetPhysics().SetVelocity(v);
		//parentObject->GetPhysics().Stop();
	}
}

glm::vec2 Collision::CalculateDistanceToObject(std::shared_ptr<GameObject> other) const
{
	if (!CanCollide(other))
		return glm::vec2();

	glm::vec2 thisTranslation = parentObject->GetTransform().GetWorldTranslation();
	glm::vec2 otherTranslation = other->GetTransform().GetWorldTranslation();

	float thisWidth = parentObject->GetCollisionMesh()->GetWidth();
	float thisHeight = parentObject->GetCollisionMesh()->GetHeight();

	float otherWidth = other->GetCollisionMesh()->GetWidth();
	float otherHeight = other->GetCollisionMesh()->GetHeight();

	float halfWidthSum = thisWidth / 2.0f + otherWidth / 2.0f;
	float halfHeigthSum = thisHeight / 2.0f + otherHeight / 2.0f;

	glm::vec2 delta = glm::abs(thisTranslation - otherTranslation) - glm::vec2(halfWidthSum, halfHeigthSum);
	return delta;
}

glm::vec2 Collision::CalculateDistanceBetweenCenters(std::shared_ptr<GameObject> other) const
{
	if (!CanCollide(other))
		return glm::vec2();

	return glm::abs(parentObject->GetTransform().GetWorldTranslation() - other->GetTransform().GetWorldTranslation());
}

glm::vec2 Collision::CalculateCollitionPoint(std::shared_ptr<GameObject> penetrated) const
{
	if (!CanCollide(penetrated))
		return glm::vec2();

	glm::vec2 b = penetrated->GetTransform().GetWorldTranslation();

	// coordinate system with a in zero
	glm::vec2 zero = parentObject->GetTransform().GetWorldTranslation();
	glm::vec2 a = glm::vec2(0.0f, 0.0f);
	b -= zero;

	glm::vec2 v = parentObject->GetPhysics().GetVelocity();
	float halfWidthB = penetrated->GetCollisionMesh()->GetWidth() / 2.0f;
	float halfHeightB = penetrated->GetCollisionMesh()->GetHeight() / 2.0f;

	float x0 = b.x - glm::sign(v.x) * halfWidthB;
	float y0 = b.y - glm::sign(v.y) * halfHeightB;

	// if penetrates from up or down
	float x = y0 * v.x / v.y;
	if (abs(x - b.x) < halfWidthB)
		return glm::vec2(x, y0) + zero;

	// if penetrates from left or right
	float y = x0 * v.y / v.x;
	if (abs(y - b.y) < halfHeightB)
		return glm::vec2(x0, y) + zero;

	return glm::vec2();
}

bool Collision::CanCollide(std::shared_ptr<GameObject> other) const
{
	return other && enabled && other->GetCollision().Enabled()
		&& parentObject->GetCollisionMesh() && other->GetCollisionMesh();
}

bool Collision::DidHitSide(std::shared_ptr<GameObject> penetrated) const
{
	if (!CanCollide(penetrated))
		return false;

	glm::vec2 b = penetrated->GetTransform().GetWorldTranslation();
	glm::vec2 v = parentObject->GetPhysics().GetVelocity();
	float halfWidthB = penetrated->GetCollisionMesh()->GetWidth() / 2.0f;
	float x0 = b.x - glm::sign(v.x) * halfWidthB;

	glm::vec2 collisionPoint = CalculateCollitionPoint(penetrated);
	return collisionPoint.x == x0;
}

