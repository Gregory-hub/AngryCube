#include "GameObjectComponent.h"

#include <utility>


GameObjectComponent::GameObjectComponent(GameObject* parent)
{
	parentObject = parent;
}

GameObjectComponent::GameObjectComponent(const GameObjectComponent& other)
{
	parentObject = nullptr;
}

GameObjectComponent& GameObjectComponent::operator=(const GameObjectComponent& other)
{
	if (this != &other)
	{
		parentObject = nullptr;
	}
	return *this;
}

GameObjectComponent::GameObjectComponent(GameObjectComponent&& other) noexcept
{
	parentObject = std::exchange(other.parentObject, nullptr);
}

GameObjectComponent& GameObjectComponent::operator=(GameObjectComponent&& other) noexcept
{
	if (this != &other)
	{
		parentObject = std::exchange(other.parentObject, nullptr);
	}
	return *this;
}

GameObject* GameObjectComponent::GetParentObject() const
{
	return parentObject;
}

void GameObjectComponent::SetParentObject(GameObject* parent)
{
	parentObject = parent;
}

