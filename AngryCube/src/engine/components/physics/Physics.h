#pragma once
#include <memory>

#include <glm/glm.hpp>

#include "engine/components/GameObjectComponent.h"
#include "engine/components/transform/Transform.h"

class GameObject;
class FlatGround;


// handles game object movement caused by any of mechanics laws
class Physics : public GameObjectComponent
{
private:
	bool enabled = true;
	std::shared_ptr<FlatGround> ground;
	float mass = 1.0f;
	glm::vec2 netForce = { 0.0f, 0.0f };
	glm::vec2 velocity = { 0.0f, 0.0f };
	glm::vec2 acceleration = { 0.0f, 0.0f };

public:
	Physics(GameObject* parentObject, float mass);
	~Physics() override = default;

	Physics(const Physics& other) = default;
	Physics& operator= (const Physics& other) = default;

	Physics(Physics&& other) noexcept = default;
	Physics& operator= (Physics&& other) noexcept = default;

	void Enable();
	void Disable();
	bool Enabled() const;

	float GetMass() const;
	void SetMass(float newMass);

	const glm::vec2& GetVelocity() const;
	void SetVelocity(const glm::vec2& newVelocity);
	
	const glm::vec2& GetAcceleration() const;

	void SetGround(const std::shared_ptr<FlatGround>& ground);
	const std::shared_ptr<FlatGround>& GetGround() const;

	void ApplyForce(glm::vec2 force);
	void RemoveForces();
	void Stop();

	void Update(float deltaTime);

private:
	void ApplyGravity();
	void ApplyAirDrag();
	void ApplyGroundDryFriction();

	void ResolveGroundCollision();
};

