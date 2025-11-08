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
