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

void Physics::SetGround(const std::shared_ptr<FlatGround>& ground)
{
	this->ground = ground;
}

const std::shared_ptr<FlatGround>& Physics::GetGround() const
{
	return ground;
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

// Apply after other forces
void Physics::ApplyGroundDryFriction()
{
	if (!ground)
		return;

	if (parentObject->GetLowestPoint().y > ground->GetHeight())
		return;

	float stictionThreshold = 0.00001f;
	if (abs(netForce.x) > stictionThreshold)
	{
		float coefOfFriction = 0.4f;
		ApplyForce(coefOfFriction * glm::vec2(1.0f, 0.0f) * abs(netForce.y) * glm::sign(netForce.x));
	}
	else
	{
		netForce.x = 0.0f;
		velocity.x = 0.0f;
	}
}

void Physics::ResolveGroundCollision()
{
	if (!ground)
		return;

	glm::vec2 lowest = parentObject->GetLowestPoint();
	if (lowest.y < ground->GetHeight())
	{
		parentObject->GetTransform().SetTranslation(glm::vec2(lowest.x, ground->GetHeight() + parentObject->GetHeight() / 2.0f));
		velocity.y = 0.0f;
	}
}

void Physics::Update(float deltaTime)
{
	if (!enabled)
		return;

	ApplyGravity();
	ApplyAirDrag();
	ApplyGroundDryFriction();

	acceleration = netForce / mass;
	velocity += acceleration * deltaTime;
	parentObject->GetTransform().Move(CM_IN_METER * velocity * deltaTime);

	netForce = { 0.0f, 0.0f };

	ResolveGroundCollision();
}

