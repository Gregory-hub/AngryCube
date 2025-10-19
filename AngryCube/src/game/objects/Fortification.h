#pragma once

#include "engine/world/GameObject.h"


class Fortification : public GameObject
{
private:
    static unsigned int id;

public:
    Fortification(Scene* parentScene);

    void Update(float deltaTime) override;
};
