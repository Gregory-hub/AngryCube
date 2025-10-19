#pragma once
#include <memory>

#include "engine/components/GameObjectComponent.h"

class GameObject;


class Collision : public GameObjectComponent
{
private:
	bool enabled = true;

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

	bool IsColliding(const std::shared_ptr<GameObject>& other) const;
};

