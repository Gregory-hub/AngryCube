#pragma once
#include <glm/vec2.hpp>

#include "engine/components/mesh/Mesh.h"
#include "engine/components/transform/Transform.h"


// handles game object movement caused by any of mechanics laws
class Physics
{
private:
	bool enabled = true;
	Transform* transform;
	Mesh* mesh;
	glm::vec2 netForce = { 0.0f, 0.0f };
	glm::vec2 velocity = { 0.0f, 0.0f };
	glm::vec2 acceleration = { 0.0f, 0.0f };
	float mass;

public:
	Physics(Transform& transform, Mesh& mesh, float mass);

	void Enable();
	void Disable();
	bool Enabled() const;

	const glm::vec2& GetVelocity() const;
	const glm::vec2& GetAcceleration() const;

	void ApplyForce(glm::vec2 force);
	void RemoveForces();
	void Stop();

	void Update(float deltaTime);

private:
	void ApplyGravity();
	void ResolveGroundCollision();
};

