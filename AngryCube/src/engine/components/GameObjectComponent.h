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

	GameObject* GetParentObject() const;
	void SetParentObject(GameObject* parent);
};

inline GameObjectComponent::~GameObjectComponent() = default;

