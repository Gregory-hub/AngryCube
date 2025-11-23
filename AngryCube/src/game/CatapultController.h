#pragma once
#include "engine/core/PlayerController.h"
#include "objects/catapult/Catapult.h"

// Processes user input
class CatapultController : public PlayerController
{
private:
    std::weak_ptr<Catapult> catapultPtr;

public:
    CatapultController(const std::weak_ptr<Catapult>& controlledCatapult);

    void ReleaseOrCock() const;
    
    float GetTension() const;
    void SetTension(float newTension) const;
    
    float GetAngle() const;
    void SetAngle(float newAngle) const;

    float GetMaxAngleLowerBound() const;
    float GetMaxAngleUpperBound() const;

    std::weak_ptr<Catapult> GetCatapult() const;
};
