#include "pch.h"
#include "GameplayHUD.h"

#include "engine/core/Game.h"


GameplayHUD::GameplayHUD()
    : catapultControls(std::make_unique<CatapultControlsWidget>()),
    levelWinWidget(std::make_unique<LevelWinWidget>()),
    levelLooseWidget(std::make_unique<LevelLooseWidget>()),
    gameWinWidget(std::make_unique<GameWinWidget>())
{
    Reset();
}

void GameplayHUD::Reset()
{
    catapultControls->Reset();
    levelWinWidget->Reset();
    levelLooseWidget->Reset();
    gameWinWidget->Reset();
}

void GameplayHUD::Render() const
{
    catapultControls->Render();
    levelWinWidget->Render();
    levelLooseWidget->Render();
    gameWinWidget->Render();
}

void GameplayHUD::ShowLevelWinWidget()
{
    levelWinWidget->Activate();
}

void GameplayHUD::ShowLevelLooseWidget()
{
    levelLooseWidget->Activate();
}

void GameplayHUD::ShowGameWinWidget()
{
    gameWinWidget->Activate();
}
