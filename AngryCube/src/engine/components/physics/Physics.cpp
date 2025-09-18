#include "Physics.h"

#include "constants.h"


Physics::Physics(Transform& transform, Mesh& mesh, float mass)
	: transform(&transform), mesh(&mesh), mass(mass)
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

void Physics::ResolveGroundCollision()
{
	//if ()
}

void Physics::Update(float deltaTime)
{
	if (!enabled)
		return;

	ApplyGravity();

	acceleration = netForce / mass;
	velocity += acceleration * deltaTime;
	transform->Move(velocity * deltaTime);

	netForce = { 0.0f, 0.0f };
}

