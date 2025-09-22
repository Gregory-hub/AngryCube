#include "GameObject.h"


GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Transform> transform)
	:	mesh(std::move(mesh)),
		transform(std::move(transform)),
		physics(std::make_shared<Physics>(this, 1.0f)),
		collision(std::make_shared<Collision>(this))
{
}

GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Transform> transform, std::shared_ptr<Physics> physics)
	:	mesh(std::move(mesh)),
		transform(std::move(transform)),
		physics(std::move(physics)),
		collision(std::make_shared<Collision>(this))
{
}

const std::string& GameObject::GetName() const
{
	return name;
}

const std::shared_ptr<Mesh>& GameObject::GetMesh()
{
	return mesh;
}

const std::shared_ptr<Transform>& GameObject::GetTransform()
{
	return transform;
}

const std::shared_ptr<Physics>& GameObject::GetPhysics()
{
	return physics;
}

const std::shared_ptr<Collision>& GameObject::GetCollision()
{
	return collision;
}

