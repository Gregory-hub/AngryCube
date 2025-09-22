#include "GameObjectContainer.h"


GameObjectContainer::GameObjectContainer(const GameObjectContainer& other)
	: transform(other.transform)
{
	for (const std::shared_ptr<GameObject>& object : other.objects)
		objects.insert(object->Clone());
}

GameObjectContainer& GameObjectContainer::operator=(const GameObjectContainer& other)
{
	if (this != &other)
	{
		transform = other.transform;
		for (const std::shared_ptr<GameObject>& object : other.objects)
			objects.insert(object->Clone());
	}
	return *this;
}

GameObjectContainer::GameObjectContainer(GameObjectContainer&& other) noexcept
	: objects(std::move(other.objects)), transform(std::move(other.transform))
{
}

GameObjectContainer& GameObjectContainer::operator=(GameObjectContainer&& other) noexcept
{
	if (this != &other)
	{
		objects = std::move(other.objects);
		transform = std::move(other.transform);
	}
	return *this;
}

const std::unordered_set<std::shared_ptr<GameObject>>& GameObjectContainer::GetObjects()
{
	std::unordered_set<std::shared_ptr<GameObject>> objectsWorldSpace = objects;
	for (const std::shared_ptr<GameObject>& object : objectsWorldSpace)
	{
		object->GetTransform().Move(transform.GetTranslation());
		object->GetTransform().Rotate(transform.GetRotation());
		object->GetTransform().Scale(transform.GetScale());
	}
	return objects;
}

void GameObjectContainer::Add(const std::shared_ptr<GameObject>& object)
{
	objects.insert(object);
	object->GetPhysics().Disable();
	object->GetTransform().Move(-transform.GetTranslation());
	object->GetTransform().Rotate(-transform.GetRotation());
	object->GetTransform().Scale(-transform.GetScale());
}

void GameObjectContainer::Remove(const std::shared_ptr<GameObject>& object)
{
	objects.erase(object);
	object->GetTransform().Move(transform.GetTranslation());
	object->GetTransform().Rotate(transform.GetRotation());
	object->GetTransform().Scale(transform.GetScale());
}

bool GameObjectContainer::Contains(const std::shared_ptr<GameObject>& object) const
{
	return objects.contains(object);
}

Transform& GameObjectContainer::GetTransform()
{
	return transform;
}

