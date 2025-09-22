#include "GameObject.h"


GameObject::GameObject()
	:	physics(Physics(this, 1.0f)),
		collision(Collision(this))
{
}

GameObject::GameObject(float mass)
	:	physics(Physics(this, mass)),
		collision(Collision(this))
{
}

GameObject::GameObject(const GameObject& other)
	: transform(other.transform), physics(other.physics), collision(other.collision)
{
    meshes.reserve(other.meshes.size());
    for (const std::shared_ptr<Mesh>& mesh : other.meshes)
        meshes.push_back(std::make_shared<Mesh>(*mesh));
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this != &other)
	{
		transform = other.transform;
		physics = other.physics;
		collision = other.collision;

		meshes.reserve(other.meshes.size());
		for (const std::shared_ptr<Mesh>& mesh : other.meshes)
			meshes.push_back(std::make_shared<Mesh>(*mesh));
	}
	return *this;
}

GameObject::GameObject(GameObject&& other) noexcept
	:	name(std::exchange(other.name, "")),
		meshes(std::move(meshes)),
		transform(std::move(other.transform)),
		physics(std::move(other.physics)),
		collision(std::move(other.collision))
{
}

GameObject& GameObject::operator=(GameObject&& other) noexcept
{
	if (this != &other)
	{
		name = std::exchange(other.name, "");
		transform = std::move(other.transform);
		physics = std::move(other.physics);
		collision = std::move(other.collision);

		meshes = std::move(other.meshes);
	}
	return *this;

}

const std::string& GameObject::GetName() const
{
	return name;
}

const std::vector<std::shared_ptr<Mesh>>& GameObject::GetMeshes()
{
	return meshes;
}

Transform& GameObject::GetTransform()
{
	return transform;
}

Physics& GameObject::GetPhysics()
{
	return physics;
}

Collision& GameObject::GetCollision()
{
	return collision;
}

