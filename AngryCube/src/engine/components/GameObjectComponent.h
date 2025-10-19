#pragma once

class GameObject;


class GameObjectComponent
{
protected:
	GameObject* parentObject = nullptr;

public:
	GameObjectComponent(GameObject* parent);
	virtual ~GameObjectComponent() = 0;

	GameObjectComponent(const GameObjectComponent& other);
	GameObjectComponent& operator= (const GameObjectComponent& other);

	GameObjectComponent(GameObjectComponent&& other) noexcept;
	GameObjectComponent& operator= (GameObjectComponent&& other) noexcept;

	virtual std::shared_ptr<GameObjectComponent> Clone() const = 0;
	virtual std::shared_ptr<GameObjectComponent> MoveClone() = 0;

	GameObject* GetParentObject() const;
	void SetParentObject(GameObject* parent);
};

inline GameObjectComponent::~GameObjectComponent() = default;

