#pragma once

#include <memory>

#include "engine/world/GameObject.h"
#include "game/interfaces/IProjectile.h"


class ProjectileCube : public GameObject, public IProjectile
{
private:
    static int id;

public:
    ProjectileCube(Scene* parentScene, float mass = 1.0f);
    ~ProjectileCube() override = default;

    ProjectileCube(const ProjectileCube& other);
    ProjectileCube& operator= (const ProjectileCube& other);

    ProjectileCube(ProjectileCube&& other) noexcept = default;
    ProjectileCube& operator= (ProjectileCube&& other) noexcept = default;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;

    void Update(float deltaTime) override;

    // Inherited via IProjectile
    void OnTargetHit(std::shared_ptr<GameObject> target) override;
};
