#pragma once
#include <glm/vec2.hpp>

#include "engine/components/transform/Transform.h"


class Physics
{
private:
	bool enabled = true;
	Transform* transform;
	glm::vec2 netForce = { 0.0f, 0.0f };
	float mass;

public:
	Physics(Transform& transform, float mass);

	void Enable();
	void Disable();
	bool Enabled() const;

	void ApplyForce(glm::vec2 force);

	void Update(float deltaTime);

private:
	void ApplyGravity();
};

