#pragma once
#include <memory>

#include "engine/components/GameObjectComponent.h"

class GameObject;


class Collision : public GameObjectComponent
{
private:
	bool enabled = false;

public:
	Collision(GameObject* parentObject);
	~Collision() override = default;

	Collision(const Collision& other) = default;
	Collision& operator= (const Collision& other) = default;

	Collision(Collision&& other) noexcept = default;
	Collision& operator= (Collision&& other) noexcept = default;
	
	std::shared_ptr<GameObjectComponent> Clone() const override;
	std::shared_ptr<GameObjectComponent> MoveClone() override;

	void Enable();
	void Disable();
	bool Enabled() const;

	bool IsColliding(std::shared_ptr<GameObject> other) const;

	void ResolveCollision(std::shared_ptr<GameObject> penetrated);

	glm::vec2 CalculateDistanceToObject(std::shared_ptr<GameObject> other) const;
	glm::vec2 CalculateDistanceBetweenCenters(std::shared_ptr<GameObject> other) const;

	glm::vec2 CalculateCollisionPoint(std::shared_ptr<GameObject> penetrated) const;

private:
	bool CanCollide(std::shared_ptr<GameObject> other) const;
	bool DidHitSide(std::shared_ptr<GameObject> other) const;

	float CalculateClosestSideX(glm::vec2 center, float halfWidth, glm::vec2 v) const;
	float CalculateClosestSideY(glm::vec2 center, float halfHeight, glm::vec2 v) const;
};

