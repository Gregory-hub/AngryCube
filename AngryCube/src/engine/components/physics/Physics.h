#pragma once
#include <memory>

#include <glm/vec2.hpp>

#include "engine/components/GameObjectComponent.h"
#include "engine/components/transform/Transform.h"
#include "engine/world/FlatGround.h"


class GameObject;


// handles game object movement caused by any of mechanics laws
class Physics : public GameObjectComponent
{
private:
	bool enabled = true;
	GameObject* parentObject;
	std::shared_ptr<FlatGround> ground;
	float mass;
	glm::vec2 netForce = { 0.0f, 0.0f };
	glm::vec2 velocity = { 0.0f, 0.0f };
	glm::vec2 acceleration = { 0.0f, 0.0f };

public:
	Physics(GameObject* parentObject, float mass);

	void Enable();
	void Disable();
	bool Enabled() const;

	const glm::vec2& GetVelocity() const;
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

