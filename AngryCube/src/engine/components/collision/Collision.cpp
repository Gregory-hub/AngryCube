#include "pch.h"
#include "Collision.h"

Collision::Collision(GameObject* parent)
    : GameObjectComponent(parent)
{
}

void Collision::Enable()
{
    enabled = true;
}

void Collision::Disable()
{
    enabled = false;
}

bool Collision::Enabled() const
{
    return enabled;
}
