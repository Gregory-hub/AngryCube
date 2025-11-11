#pragma once

#include <queue>

#include "engine/world/GameObject.h"
#include <game/interfaces/IDestructable.h>
#include <game/interfaces/IDestructableContainer.h>


class Fortification : public GameObject, public IDestructableContainer
{
private:
    static int id;

protected:
    std::queue<std::shared_ptr<IDestructable>> destructionQueue;

public:
    Fortification(Scene* parentScene);

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    void Update(float deltaTime) override;

    void AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed) override;

    void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;

private:
    void DestroyObjectsInQueue() override;
};
