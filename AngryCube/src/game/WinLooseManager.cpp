#include "pch.h"
#include "WinLooseManager.h"

#include "engine/core/Game.h"

void WinLooseManager::OnLevelWin()
{
    if (Game::GameLevelManager->GetCurrentLevelIndex() == Game::GameLevelManager->GetLevelCount() - 1)
        OnGameWin();
    else
        Game::GameHUD->ShowLevelWinWidget();
}

void WinLooseManager::OnLevelLoose()
{
    Game::GameHUD->ShowLevelLooseWidget();
}

void WinLooseManager::OnGameWin()
{
    Game::GameHUD->ShowGameWinWidget();
}
