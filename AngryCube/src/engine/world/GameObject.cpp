#include "GameObject.h"

#include "engine/core/Game.h"


GameObject::GameObject(float mass, const std::shared_ptr<CollisionMesh>& collisionMesh)
	:	transform(Transform(this)),
		physics(Physics(this, mass)),
		collision(Collision(this)),
		collisionMesh(collisionMesh)
{
}

GameObject::GameObject(const GameObject& other)
	:	transform(other.transform),
		physics(other.physics),
		collision(other.collision),
		collisionMesh(other.collisionMesh)
{
	transform.SetParentObject(this);
	physics.SetParentObject(this);
	collision.SetParentObject(this);

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
		collisionMesh = other.collisionMesh;

		transform.SetParentObject(this);
		physics.SetParentObject(this);
		collision.SetParentObject(this);

		meshes.clear();
		meshes.reserve(other.meshes.size());
		for (const std::shared_ptr<Mesh>& mesh : other.meshes)
			meshes.push_back(std::make_shared<Mesh>(*mesh));
	}
	return *this;
}

GameObject::GameObject(GameObject&& other) noexcept
	:	name(std::exchange(other.name, "")),
		meshes(std::move(other.meshes)),
		transform(std::move(other.transform)),
		physics(std::move(other.physics)),
		collision(std::move(other.collision)),
		collisionMesh(std::move(other.collisionMesh))
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
		collisionMesh = std::move(other.collisionMesh);
	}
	return *this;
}

GameObject* GameObject::GetParent() const
{
	return parent;
}

const std::unordered_set<std::shared_ptr<GameObject>>& GameObject::GetChildren() const
{
	return children;
}

bool GameObject::HasChild(const std::shared_ptr<GameObject>& child) const
{
	return children.contains(child);
}

void GameObject::AttachChild(const std::shared_ptr<GameObject>& child)
{
	if (child->parent)
		child->parent->RemoveChild(child);

	if (child)
	{
		children.insert(child);
		child->parent = this;
		child->GetPhysics().Disable();
	}
}

void GameObject::RemoveChild(const std::shared_ptr<GameObject>& child)
{
	if (child)
	{
		children.erase(child);
		child->parent = nullptr;
	}
}

const std::string& GameObject::GetName() const
{
	return name;
}

const std::vector<std::shared_ptr<Mesh>>& GameObject::GetMeshes()
{
	return meshes;
}

std::shared_ptr<CollisionMesh> GameObject::GetCollisionMesh()
{
	return collisionMesh;
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

