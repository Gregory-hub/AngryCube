#pragma once
#include <memory>
#include <unordered_set>

#include "GameObject.h"


class GameObjectContainer
{
private:
	std::unordered_set<std::shared_ptr<GameObject>> objects;
	Transform transform;

public:
	GameObjectContainer() = default;
	virtual ~GameObjectContainer() = 0;

	GameObjectContainer(const GameObjectContainer& other);
	GameObjectContainer& operator= (const GameObjectContainer& other);

	GameObjectContainer(GameObjectContainer&& other) noexcept;
	GameObjectContainer& operator= (GameObjectContainer&& other) noexcept;

	const std::unordered_set<std::shared_ptr<GameObject>>& GetObjects();
	void Add(const std::shared_ptr<GameObject>& object);
	void Remove(const std::shared_ptr<GameObject>& object);
	bool Contains(const std::shared_ptr<GameObject>& object) const;

	Transform& GetTransform();
};

inline GameObjectContainer::~GameObjectContainer() = default;

