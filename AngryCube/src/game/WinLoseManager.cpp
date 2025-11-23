#include "pch.h"
#include "WinLoseManager.h"

#include "engine/core/Game.h"

void WinLoseManager::OnLevelWin()
{
    if (Game::GameLevelManager->GetCurrentLevelIndex() == Game::GameLevelManager->GetLevelCount() - 1)
        OnGameWin();
    else
        Game::GameHUD->ShowLevelWinWidget();
}

void WinLoseManager::OnLevelLoose()
{
    Game::GameHUD->ShowLevelLooseWidget();
}

void WinLoseManager::OnGameWin()
{
    Game::GameHUD->ShowGameWinWidget();
}
