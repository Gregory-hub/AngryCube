#include "Cube.h"

#include <stdexcept>

#include "engine/components/mesh/DefaultMeshes.h"
#include "engine/material/SolidColor.h"


int Cube::id = 0;

Cube::Cube(Scene* parentScene, float mass)
	: GameObject(parentScene, mass, std::make_shared<CollisionMesh>(std::make_shared<CubeMesh>()))
{
    name = "Cube " + std::to_string(id++);

    std::shared_ptr<CubeMesh> mesh = std::make_shared<CubeMesh>();
    mesh->SetMaterial(std::make_shared<SolidColor>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    meshes.push_back(mesh);
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
