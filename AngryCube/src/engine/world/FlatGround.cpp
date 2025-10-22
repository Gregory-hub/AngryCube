#include "pch.h"
#include "FlatGround.h"

#include "engine/materials/SolidColor.h"
#include <engine/components/mesh/DefaultMeshes.h>


unsigned FlatGround::id = 0;

FlatGround::FlatGround(Scene* parentScene, float height)
	: GameObject(parentScene, 0.0f), height(height)
{
	name = "FlatGround " + std::to_string(id++);

    std::shared_ptr<CubeMesh> mesh = std::make_shared<CubeMesh>();
    mesh->SetMaterial(std::make_shared<SolidColor>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    meshes.push_back(mesh);

	glm::vec4 color(0.145f, 0.349f, 0.12f, 1.0f);

	for (auto& mesh : GetMeshes())
		mesh->SetMaterial(std::make_shared<SolidColor>(color));

	GetTransform().SetScale(glm::vec2(10.0f, height / 100.0f));
	GetTransform().SetTranslation(glm::vec2(500.0f, height / 2.0f));

	GetPhysics().Disable();
	GetCollision().Disable();

	//collisionMesh = std::make_shared<CollisionMesh>(this, std::make_shared<CubeMesh>());
}

FlatGround::FlatGround(const FlatGround& other)
	: GameObject(other)
{
    name = "FlatGround " + std::to_string(id++);
}

FlatGround& FlatGround::operator=(const FlatGround& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        name = "FlatGround " + std::to_string(id++);
    }
	return *this;
}

std::shared_ptr<GameObject> FlatGround::Clone() const
{
    return std::make_shared<FlatGround>(*this);
}

std::shared_ptr<GameObject> FlatGround::MoveClone()
{
    return std::make_shared<FlatGround>(std::move(*this));
}

float FlatGround::GetHeight() const
{
	return height;
}

void FlatGround::SetHeight(float newHeight)
{
	height = newHeight;
	GetTransform().SetScale(glm::vec2(100.0f, height / 100.0f));
	GetTransform().SetTranslation(glm::vec2(500.0f, height / 2.0f));
}

void FlatGround::Update(float deltaTime)
{
}
