#pragma once
#include "engine/core/Level.h"
#include "game/objects/catapult/Catapult.h"


class Level1 : public Level
{
private:
	std::shared_ptr<Catapult> catapult;
	
public:
	Level1();

	std::shared_ptr<Catapult> GetCatapult() const;
};

