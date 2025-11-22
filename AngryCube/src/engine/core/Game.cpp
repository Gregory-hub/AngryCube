#include "pch.h"
#include "Game.h"

void Game::OnLevelWin()
{
    GameLevelManager->LoadNext();
}
