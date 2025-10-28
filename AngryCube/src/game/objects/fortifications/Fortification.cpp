#include "pch.h"
#include "Fortification.h"

#include "engine/world/Scene.h"


int Fortification::id = 0;

Fortification::Fortification(Scene* parentScene)
    : GameObject(parentScene, 0.0f)
{
    name = "Fortification " + std::to_string(id++);
}

void Fortification::Update(float deltaTime)
{
    DestroyObjectsInQueue();
}

void Fortification::AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed)
{
    destructionQueue.push(destroyed);
}

void Fortification::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
}

void Fortification::DestroyObjectsInQueue()
{
    while (!destructionQueue.empty())
    {
        std::shared_ptr<IDestructable> destroyed = destructionQueue.front();
		destructionQueue.pop();

        if (auto object = std::dynamic_pointer_cast<GameObject>(destroyed))
        {
            RemoveChild(object);
            scene->Remove(object);
        }
    }
}
