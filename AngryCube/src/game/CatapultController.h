#pragma once
#include "engine/core/PlayerController.h"
#include "objects/catapult/Catapult.h"

class CatapultController : public PlayerController
{
private:
    std::weak_ptr<Catapult> catapultPtr;
    
public:
    CatapultController(const std::weak_ptr<Catapult>& controlledCatapult);

    void ReleaseOrCock() const;
};
