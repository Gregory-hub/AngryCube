#include "pch.h"
#include "GameStateManager.h"

#include "engine/core/Game.h"

void GameStateManager::OnLevelWin()
{
    if (Game::GameLevelManager->GetCurrentLevelIndex() == Game::GameLevelManager->GetLevelCount() - 1)
        OnGameWin();
    else
        Game::GameLevelManager->LoadNext();
}

void GameStateManager::OnLevelLoose()
{
}

void GameStateManager::OnGameWin()
{
}
