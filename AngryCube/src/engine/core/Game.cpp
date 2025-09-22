#include "Game.h"


void Game::LoadLevel(const std::shared_ptr<Level>& level)
{
	activeLevel = level;
}

const std::shared_ptr<Level>& Game::GetActiveLevel()
{
	return activeLevel;
}

