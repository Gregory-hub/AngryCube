#pragma once

#include <memory>

#include "engine/destruction/IDestructable.h"
#include "engine/world/GameObject.h"
#include "game/interfaces/IProjectile.h"


class ProjectileCube :
    public GameObject,
    public IProjectile,
    public IDestructable,
    public std::enable_shared_from_this<ProjectileCube>
{
private:
    static int id;

    float selfDestructDelay = 0.5f;
    float selfDestructTimer = 0.0f;

    bool lastOne = false;

public:
    ProjectileCube(Scene* parentScene, float mass = 1.0f);
    ~ProjectileCube() override = default;

    ProjectileCube(const ProjectileCube& other);
    ProjectileCube& operator= (const ProjectileCube& other);

    ProjectileCube(ProjectileCube&& other) noexcept = default;
    ProjectileCube& operator= (ProjectileCube&& other) noexcept = default;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    bool IsReleased() const;

    void MarkAsLast() override;

    void Destroy() override;
    void OnDestructon() override;

    void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;

    void Update(float deltaTime) override;

    // Inherited via IProjectile
    void OnTargetHit(std::shared_ptr<GameObject> target) override;
};
