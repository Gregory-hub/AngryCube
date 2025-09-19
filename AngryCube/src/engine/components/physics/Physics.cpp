#include "Physics.h"

#include "constants.h"
#include "engine/world/GameObject.h"


Physics::Physics(GameObject* parentObject, float mass)
	: parentObject(parentObject), mass(mass)
{
}

void Physics::Enable()
{
	enabled = true;
}

void Physics::Disable()
{
	enabled = false;
	RemoveForces();
	Stop();
}

bool Physics::Enabled() const
{
	return enabled;
}

const glm::vec2& Physics::GetVelocity() const
{
	return velocity;
}

const glm::vec2& Physics::GetAcceleration() const
{
	return acceleration;
}

void Physics::ApplyForce(glm::vec2 force)
{
	if (!enabled)
		return;
	netForce += force;
}

void Physics::RemoveForces()
{
	netForce = { 0.0f, 0.0f };
}

void Physics::Stop()
{
	velocity = { 0.0f, 0.0f };
}

void Physics::ApplyGravity()
{
	ApplyForce(glm::vec2({ 0.0f, -1.0f }) * G * mass);
}

void Physics::ApplyAirDrag()
{
	if (velocity == glm::vec2(0.0f, 0.0f))
		return;

	glm::vec2 direction = glm::normalize(velocity);

	float airDensity = 1.2f;
	float dragCoef = 0.5f;
	float area = abs(direction.x * parentObject->GetWidth() / CM_IN_METER + direction.y * parentObject->GetHeight() / CM_IN_METER);
	float mult = 0.5f * airDensity * area * dragCoef;

	glm::vec2 dragForce = mult * glm::pow(glm::length(velocity), 2.0f) * direction;
	ApplyForce(-dragForce);
}

void Physics::ResolveGroundCollision(const std::shared_ptr<FlatGround>& ground)
{
	glm::vec2 lowest = parentObject->GetLowestPoint();
	if (lowest.y < ground->GetHeight())
	{
		parentObject->GetTransform()->SetTranslation(glm::vec2(lowest.x, ground->GetHeight() + parentObject->GetHeight() / 2.0f));
		velocity.y = 0.0f;
	}
}

void Physics::Update(float deltaTime)
{
	if (!enabled)
		return;

	ApplyGravity();
	ApplyAirDrag();

	acceleration = netForce / mass;
	velocity += acceleration * deltaTime;
	parentObject->GetTransform()->Move(velocity * deltaTime);

	netForce = { 0.0f, 0.0f };
}

