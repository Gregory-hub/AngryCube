#include "Physics.h"

#include "constants.h"


Physics::Physics(Transform& transform, float mass)
	: transform(&transform), mass(mass)
{
}

void Physics::Enable()
{
	enabled = true;
}

void Physics::Disable()
{
	enabled = false;
}

bool Physics::Enabled() const
{
	return enabled;
}

void Physics::ApplyForce(glm::vec2 force)
{
	netForce += force;
}

void Physics::ApplyGravity()
{
	ApplyForce(glm::vec2({ 0.0f, -1.0f }) * G * mass);
}

void Physics::Update(float deltaTime)
{
	ApplyGravity();

	glm::vec2 movement = netForce / mass * deltaTime * deltaTime;
	transform->Move(movement);
}

