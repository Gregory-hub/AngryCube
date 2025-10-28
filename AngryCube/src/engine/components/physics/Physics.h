#pragma once
#include <memory>

#include <glm/glm.hpp>

#include "engine/components/GameObjectComponent.h"
#include "PhysicsMaterial.h"

class GameObject;
class FlatGround;


// handles game object movement caused by any of mechanics laws
class Physics : public GameObjectComponent
{
private:
	bool enabled = false;
	float mass = 1.0f;
	glm::vec2 netForce = { 0.0f, 0.0f };
	glm::vec2 velocity = { 0.0f, 0.0f };
	glm::vec2 acceleration = { 0.0f, 0.0f };

	std::shared_ptr<PhysicsMaterial> physicsMaterial;

public:
	Physics(GameObject* parentObject, float mass);
	~Physics() override = default;

	Physics(const Physics& other) = default;
	Physics& operator= (const Physics& other) = default;

	Physics(Physics&& other) noexcept = default;
	Physics& operator= (Physics&& other) noexcept = default;

	std::shared_ptr<GameObjectComponent> Clone() const override;
	std::shared_ptr<GameObjectComponent> MoveClone() override;

	void Enable();
	void Disable();
	bool Enabled() const;

	float GetMass() const;
	void SetMass(float newMass);

	const glm::vec2& GetVelocity() const;
	void SetVelocity(const glm::vec2& newVelocity);
	
	const glm::vec2& GetAcceleration() const;

	void SetPhysicsMaterial(std::shared_ptr<PhysicsMaterial> newPhysicsMaterial);
	std::shared_ptr<PhysicsMaterial> GetPhysicsMaterial() const;

	void ApplyForce(glm::vec2 force);
	void RemoveForces();
	void Stop();

	void Update(float deltaTime);
	void PostUpdate(float deltaTime);

	void OnCollision(std::shared_ptr<GameObject> other, bool didHitSide);

private:
	void MoveDueToInertia(float deltaTime);
	void MoveDueToForces(float deltaTime);
	void ApplyGravity();
	void ApplyAirDrag();
	void ApplyDryFriction(std::shared_ptr<GameObject> other);
};

