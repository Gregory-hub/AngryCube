#include "pch.h"
#include "Physics.h"

#include "constants.h"
#include "engine/world/GameObject.h"
#include "engine/world/FlatGround.h"


Physics::Physics(GameObject* parentObject, float mass)
	: GameObjectComponent(parentObject), mass(mass)
{
}

std::shared_ptr<GameObjectComponent> Physics::Clone() const
{
	return std::make_shared<Physics>(*this);
}

std::shared_ptr<GameObjectComponent> Physics::MoveClone()
{
	return std::make_shared<Physics>(std::move(*this));
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

float Physics::GetMass() const
{
	return mass;
}

void Physics::SetMass(float newMass)
{
	mass = newMass;
}

const glm::vec2& Physics::GetVelocity() const
{
	return velocity;
}

void Physics::SetVelocity(const glm::vec2& newVelocity)
{
	if (!enabled)
		return;
	velocity = newVelocity;
}

const glm::vec2& Physics::GetAcceleration() const
{
	return acceleration;
}

void Physics::SetPhysicsMaterial(std::shared_ptr<PhysicsMaterial> newPhysicsMaterial)
{
	physicsMaterial = newPhysicsMaterial;
}

std::shared_ptr<PhysicsMaterial> Physics::GetPhysicsMaterial() const
{
	return physicsMaterial;
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
	float area = abs(direction.x * parentObject->GetCollisionMesh()->GetWidth() / CM_IN_METER + direction.y * parentObject->GetCollisionMesh()->GetHeight() / CM_IN_METER);
	float mult = 0.5f * airDensity * area * dragCoef;

	glm::vec2 dragForce = mult * glm::pow(glm::length(velocity), 2.0f) * direction;
	ApplyForce(-dragForce);
}

void Physics::ApplyDryFriction(std::shared_ptr<GameObject> other)
{
	if (!other || !other->GetPhysics().GetPhysicsMaterial())
		return;

	float forceY = netForce.y - G * mass;

	if (forceY < 0.0f && abs(velocity.x) > other->GetPhysics().GetPhysicsMaterial()->StictionThreshold)
	{
		ApplyForce(GetPhysicsMaterial()->FrictionCoefficient * glm::vec2(1.0f, 0.0f) * forceY * glm::sign(velocity.x));
	}
	else
	{
		netForce.x = 0.0f;
		velocity.x = 0.0f;
	}
}

void Physics::Update(float deltaTime)
{
	if (!enabled || !parentObject->GetCollisionMesh())
		return;

	ApplyGravity();
	ApplyAirDrag();

	acceleration = netForce / mass;
	velocity += acceleration * deltaTime;
	parentObject->GetTransform().Move(CM_IN_METER * velocity * deltaTime);

	netForce = { 0.0f, 0.0f };
}

void Physics::OnCollision(std::shared_ptr<GameObject> other, bool applyDryFriction)
{	
	if (!enabled || !parentObject->GetCollisionMesh())
		return;

	if (applyDryFriction)
		ApplyDryFriction(other);
}
