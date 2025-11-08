#include "pch.h"
#include "CatapultController.h"

CatapultController::CatapultController(const std::weak_ptr<Catapult>& controlledCatapult)
    : catapultPtr(controlledCatapult)
{
}

void CatapultController::ReleaseOrCock() const
{
    if (auto catapult = catapultPtr.lock())
    {
        if (catapult->ReadyToRelease())
            catapult->Release();
        else
            catapult->Cock();
    }
}

float CatapultController::GetTension() const
{
    if (auto catapult = catapultPtr.lock())
        return catapult->GetSpringTension();
    return 0.0f;
}

void CatapultController::SetTension(float newTension) const
{
    if (auto catapult = catapultPtr.lock())
        catapult->SetSpringTension(newTension);
}

float CatapultController::GetAngle() const
{
    if (auto catapult = catapultPtr.lock())
        return catapult->GetAngle();
    return 0.0f;
}

void CatapultController::SetAngle(float newAngle) const
{
    if (auto catapult = catapultPtr.lock())
        catapult->SetAngle(newAngle);
}
