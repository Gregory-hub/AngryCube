#include "pch.h"
#include "GameplayHUD.h"

#include "engine/core/Game.h"


GameplayHUD::GameplayHUD()
    : catapultControls(std::make_unique<CatapultControlsWidget>())
{
    Reset();
}

void GameplayHUD::Reset()
{
    catapultControls->Reset();
}

void GameplayHUD::Render() const
{
    catapultControls->Render();
}
