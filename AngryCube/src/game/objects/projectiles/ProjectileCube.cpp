#include "pch.h"
#include "ProjectileCube.h"

#include "engine/components/mesh/DefaultMeshes.h"
#include "engine/materials/SolidColor.h"
#include "game/objects/fortification/Brick.h"
#include <game/interfaces/IDestructableContainer.h>

#include "game/objects/fortification/Fortification.h"


int ProjectileCube::id = 0;

ProjectileCube::ProjectileCube(Scene* parentScene, float mass)
	: GameObject(parentScene, mass, std::make_shared<CollisionMesh>(this, std::make_shared<CubeMesh>()))
{
    name = "ProjectileCube " + std::to_string(id++);

    GetCollision().Enable();
    GetPhysics().Enable();

    GetPhysics().SetPhysicsMaterial(std::make_shared<PhysicsMaterial>(1.2f, 0.00001f));

    std::shared_ptr<CubeMesh> mesh = std::make_shared<CubeMesh>();
    mesh->SetMaterial(std::make_shared<SolidColor>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    meshes.push_back(mesh);
}

ProjectileCube::ProjectileCube(const ProjectileCube& other)
	: GameObject(other)
{
    name = "ProjectileCube " + std::to_string(id++);
}

ProjectileCube& ProjectileCube::operator=(const ProjectileCube& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        name = "ProjectileCube " + std::to_string(id++);
    }
	return *this;
}

std::shared_ptr<GameObject> ProjectileCube::Clone() const
{
    return std::make_shared<ProjectileCube>(*this);
}

std::shared_ptr<GameObject> ProjectileCube::MoveClone()
{
    return std::make_shared<ProjectileCube>(std::move(*this));
}

void ProjectileCube::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
    if (auto brick = std::dynamic_pointer_cast<Brick>(other))
    {
        if (auto fort = dynamic_cast<Fortification*>(other->GetParent()))
            fort->SetWinGameEnabled(true);
        OnTargetHit(other);
    }
    else
    {
        GetCollision().ResolveCollision(other);
    }
}

void ProjectileCube::Update(float deltaTime)
{
}

void ProjectileCube::OnTargetHit(std::shared_ptr<GameObject> target)
{
    glm::vec2 v0 = GetPhysics().GetVelocity();
    float m0 = GetPhysics().GetMass();
    float m1 = target->GetPhysics().GetMass();
    GetPhysics().SetVelocity(v0 * glm::clamp(m0 / m1, 0.5f, 0.75f));
}
