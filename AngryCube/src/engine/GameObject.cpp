#include "GameObject.h"


const std::string& GameObject::GetName() const
{
	return name;
}

const std::shared_ptr<Mesh>& GameObject::GetMesh()
{
	return mesh;
}

const std::shared_ptr<Movement>& GameObject::GetMovement()
{
	return movement;
}

