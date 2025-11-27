#include "pch.h"
#include "WinLoseManager.h"

#include "engine/core/Game.h"

void WinLoseManager::OnLevelWin()
{
    if (status != WinStatus::None)
        return;
    status = WinStatus::WinLevel;

    if (Game::GameLevelManager->GetCurrentLevelIndex() == Game::GameLevelManager->GetLevelCount() - 1)
        OnGameWin();
    else
        Game::GameHUD->ShowLevelWinWidget();
}

void WinLoseManager::OnLevelLoose()
{
    if (status != WinStatus::None)
        return;
    status = WinStatus::LoseLevel;

    Game::GameHUD->ShowLevelLooseWidget();
}

void WinLoseManager::OnGameWin()
{
    if (!(status == WinStatus::None || status == WinStatus::WinLevel))
        return;
    status = WinStatus::WinGame;

    Game::GameHUD->ShowGameWinWidget();
}

void WinLoseManager::Reset()
{
    status = WinStatus::None;
}
