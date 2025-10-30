#pragma once
#include <memory>

#include "engine/components/GameObjectComponent.h"
#include "engine/components/collision/Collision.h"

class GameObject;


class CubeCollision : public Collision
{
public:
	CubeCollision(GameObject* parent);
	~CubeCollision() override = default;

	CubeCollision(const CubeCollision& other) = default;
	CubeCollision& operator= (const CubeCollision& other) = default;

	CubeCollision(CubeCollision&& other) noexcept = default;
	CubeCollision& operator= (CubeCollision&& other) noexcept = default;
	
	std::shared_ptr<GameObjectComponent> Clone() const override;
	std::shared_ptr<GameObjectComponent> MoveClone() override;

	void Enable() override;
	void Disable() override;
	bool Enabled() const override;

	bool IsColliding(std::shared_ptr<GameObject> other) const;

	void ResolveCollision(std::shared_ptr<GameObject> penetrated);

	glm::vec2 CalculateDistanceToObject(std::shared_ptr<GameObject> other) const;
	glm::vec2 CalculateDistanceBetweenCenters(std::shared_ptr<GameObject> other) const;

	glm::vec2 CalculateCollisionPoint(std::shared_ptr<GameObject> penetrated) const;

private:
	bool CanCollide(std::shared_ptr<GameObject> other) const;
	bool DidHitSide(std::shared_ptr<GameObject> other, glm::vec2 collisionPoint) const;

	float CalculateClosestSideX(glm::vec2 center, float halfWidth, glm::vec2 v) const;
	float CalculateClosestSideY(glm::vec2 center, float halfHeight, glm::vec2 v) const;
};
