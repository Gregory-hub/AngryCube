#include "Cube.h"

#include <stdexcept>

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/components/mesh/DefaultMeshes.h"


int Cube::id = 0;

Cube::Cube(float mass)
	: GameObject(mass, std::make_shared<CollisionMesh>(std::make_shared<CubeMesh>()))
{
    name = "Cube " + std::to_string(id++);
    meshes.push_back(GetCollisionMesh()->GetBaseMesh());
}

Cube::Cube(const Cube& other)
	: GameObject(other)
{
    name = "Cube " + std::to_string(id++);
}

Cube& Cube::operator=(const Cube& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        name = "Cube " + std::to_string(id++);
    }
	return *this;
}

std::shared_ptr<GameObject> Cube::Clone() const
{
    return std::make_shared<Cube>(*this);
}

std::shared_ptr<GameObject> Cube::MoveClone()
{
    return std::make_shared<Cube>(std::move(*this));
}

void Cube::Update(float deltaTime)
{
}

void Cube::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
}
