#include "GameObject.h"


GameObject::GameObject(Mesh mesh, Transform transform)
	: mesh(std::move(mesh)), transform(std::move(transform)), physics(this->transform, this->mesh, 1.0f)
{
}

const std::string& GameObject::GetName() const
{
	return name;
}

Mesh& GameObject::GetMesh()
{
	return mesh;
}

Transform& GameObject::GetTransform()
{
	return transform;
}

Physics& GameObject::GetPhysics()
{
	return physics;
}

