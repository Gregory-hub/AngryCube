#pragma once
#include "engine/core/Level.h"
#include "game/objects/catapult/Catapult.h"
#include "game/objects/fortifications/Fortification.h"


class AngryCubeLevel : public Level
{
private:
	std::shared_ptr<Catapult> catapult;
	std::shared_ptr<Fortification> fortification;
	
public:
	AngryCubeLevel(std::string levelName);

	std::shared_ptr<Catapult> GetCatapult() const;
	void SetCatapult(std::shared_ptr<Catapult> newCatapult);
	
	std::shared_ptr<Fortification> GetFortification() const;
	void SetFortification(std::shared_ptr<Fortification> newFortification);
};
