#pragma once

#include <queue>

#include "engine/world/GameObject.h"
#include <game/interfaces/IDestructable.h>
#include <game/interfaces/IDestructableContainer.h>


class Fortification : public GameObject, public IDestructableContainer
{
private:
    static unsigned int id;

protected:
    std::queue<std::shared_ptr<IDestructable>> destructionQueue;

public:
    Fortification(Scene* parentScene);

    void Update(float deltaTime) override;

    void AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed) override;

private:
    void DestroyObjectsInQueue() override;
};
