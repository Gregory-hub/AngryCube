#pragma once

#include <glm/glm.hpp>

#include "Transform.h"


class Movement
{
private:
	Transform transform;

public:
	Movement() = default;
	~Movement() = default;

	Movement(const Movement& other) = default;
	Movement& operator= (const Movement& other) = default;

	Movement(Movement&& other) = default;
	Movement& operator= (Movement&& other) = default;

	Transform& GetTransform();
	const Transform& GetTransform() const;

	void Move(const glm::vec2& value);
	void Rotate(const float value);
	void Scale(const glm::vec2& value);

	glm::mat4 GetTransformMatrix() const;
};

