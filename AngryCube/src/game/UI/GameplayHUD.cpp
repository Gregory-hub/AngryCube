#include "pch.h"
#include "GameplayHUD.h"

#include "engine/core/Game.h"
#include "game/CatapultController.h"
#include "game/objects/catapult/Catapult.h"


GameplayHUD::GameplayHUD()
    : catapultControls(std::make_unique<CatapultControlsWidget>()),
    levelWinWidget(std::make_unique<LevelWinWidget>())
{
    Reset();
}

void GameplayHUD::Reset()
{
    catapultControls->Reset();
    levelWinWidget->Reset();
}

void GameplayHUD::Render() const
{
    catapultControls->Render();
    levelWinWidget->Render();
}

void GameplayHUD::ShowLevelWinWidget()
{
    levelWinWidget->Activate();
}

void GameplayHUD::ShowLevelLooseWidget()
{
}

void GameplayHUD::ShowGameWinWidget()
{
}
