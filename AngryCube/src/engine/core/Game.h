#pragma once
#include <memory>

#include "Level.h"


// handles game state (active level, etc.)
class Game
{
private:
	std::shared_ptr<Level> activeLevel;

public:
	void LoadLevel(const std::shared_ptr<Level>& level);
	const std::shared_ptr<Level>& GetActiveLevel();
};
