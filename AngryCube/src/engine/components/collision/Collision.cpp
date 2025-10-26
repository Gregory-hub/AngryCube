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
	return d.x < 0.0f && d.y < 0.0f;
}

void Collision::ResolveCollision(std::shared_ptr<GameObject> penetrated)
{
	if (!CanCollide(penetrated))
		return;

	glm::vec2 d = CalculateDistanceToObject(penetrated);
	glm::vec2 v0 = parentObject->GetPhysics().GetVelocity();
	glm::vec2 v1 = penetrated->GetPhysics().GetVelocity();
	glm::vec2 dv = v0 - v1;
	if (d.x < 0.0f && d.y < 0.0f && glm::length(v0) >= glm::length(v1))
	{
		float k = 0.0f;
		if (abs(d.x) <= abs(d.y) && abs(dv.x) != 0.0f)
			k = abs(d.x / dv.x);
		else if (abs(d.x) >= abs(d.y) && abs(dv.y) != 0.0f)
			k = abs(d.y / dv.y);

		glm::vec2 moveBack = -k * dv;

		glm::vec2 collisionPoint = CalculateCollisionPoint(penetrated);
		bool didHitSide = DidHitSide(penetrated, collisionPoint);
		if (didHitSide)		// Hit from left or right
		{
			moveBack.y = 0.0f;
			v0.x -= dv.x;
		}
		else				// Hit from up or down
		{
			moveBack.x = 0.0f;
			v0.y -= dv.y;
		}

		parentObject->GetTransform().Move(moveBack);
		parentObject->GetPhysics().SetVelocity(v0);
		parentObject->GetPhysics().OnCollision(penetrated, !didHitSide);
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

glm::vec2 Collision::CalculateCollisionPoint(std::shared_ptr<GameObject> penetrated) const
{
	if (!CanCollide(penetrated))
		return glm::vec2();

	glm::vec2 b = penetrated->GetTransform().GetWorldTranslation();

	// use coordinate system with parentObject in zero
	glm::vec2 zero = parentObject->GetTransform().GetWorldTranslation();
	glm::vec2 a = glm::vec2(0.0f, 0.0f);
	b -= zero;

	glm::vec2 v = parentObject->GetPhysics().GetVelocity();
	float halfWidthB = penetrated->GetCollisionMesh()->GetWidth() / 2.0f;
	float halfHeightB = penetrated->GetCollisionMesh()->GetHeight() / 2.0f;

	float x0 = CalculateClosestSideX(b, halfWidthB, v);
	float y0 = CalculateClosestSideY(a, halfHeightB, v);

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
	return other && other.get() != parentObject && enabled && other->GetCollision().Enabled()
		&& parentObject->GetCollisionMesh() && other->GetCollisionMesh();
}

bool Collision::DidHitSide(std::shared_ptr<GameObject> penetrated, glm::vec2 collisionPoint) const
{
	if (!CanCollide(penetrated))
		return false;

	glm::vec2 b = penetrated->GetTransform().GetWorldTranslation();
	glm::vec2 v = parentObject->GetPhysics().GetVelocity();
	float halfWidthB = penetrated->GetCollisionMesh()->GetWidth() / 2.0f;

	float x0 = CalculateClosestSideX(b, halfWidthB, v);

	return collisionPoint.x == x0;
}

float Collision::CalculateClosestSideX(glm::vec2 center, float halfWidth, glm::vec2 v) const
{
	float x0 = center.x;
	if (v.x < 0)
		x0 += halfWidth;
	else
		x0 -= halfWidth;
	return x0;
}

float Collision::CalculateClosestSideY(glm::vec2 center, float halfHeight, glm::vec2 v) const
{
	float y0 = center.y;
	if (v.y < 0)
		y0 += halfHeight;
	else
		y0 -= halfHeight;
	return y0;
}

