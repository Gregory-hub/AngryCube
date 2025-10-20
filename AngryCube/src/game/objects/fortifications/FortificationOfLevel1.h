#pragma once
#include "game/objects/fortifications/Fortification.h"


class FortificationOfLevel1 : public Fortification
{
public:
    FortificationOfLevel1(Scene* parentScene);
    
    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;
};
