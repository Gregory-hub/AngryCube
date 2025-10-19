#include "pch.h"
#include "Fortification.h"


unsigned int Fortification::id = 0;

Fortification::Fortification(Scene* parentScene)
    : GameObject(parentScene, 0.0f)
{
    name = "Fortification " + std::to_string(id++);
}

void Fortification::Update(float deltaTime)
{
}
