#include "pch.h"
#include "Fortification.h"

#include "engine/world/Scene.h"


int Fortification::id = 0;

Fortification::Fortification(Scene* parentScene)
    : GameObject(parentScene, 0.0f)
{
    name = "Fortification " + std::to_string(id++);
}

std::shared_ptr<GameObject> Fortification::Clone() const
{
    return std::make_shared<Fortification>(*this);
}

std::shared_ptr<GameObject> Fortification::MoveClone()
{
    return std::make_shared<Fortification>(std::move(*this));
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
