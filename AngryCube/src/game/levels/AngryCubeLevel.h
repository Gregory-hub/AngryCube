#pragma once
#include "engine/core/Level.h"
#include "game/objects/catapult/Catapult.h"
#include "game/objects/fortification/Fortification.h"


class AngryCubeLevel : public Level
{
private:
	std::shared_ptr<Catapult> catapult;
	std::shared_ptr<Fortification> fortification;
	
public:
	AngryCubeLevel(std::string levelName);
	~AngryCubeLevel() override = default;

	AngryCubeLevel(const AngryCubeLevel& other) = default;
	AngryCubeLevel& operator= (const AngryCubeLevel& other) = default;

	AngryCubeLevel(AngryCubeLevel&& other) noexcept = default;
	AngryCubeLevel& operator= (AngryCubeLevel&& other) noexcept = default;

	std::shared_ptr<Catapult> GetCatapult() const;
	void SetCatapult(std::shared_ptr<Catapult> newCatapult);
	
	std::shared_ptr<Fortification> GetFortification() const;
	void SetFortification(std::shared_ptr<Fortification> newFortification);
};
