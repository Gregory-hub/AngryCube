#include "pch.h"
#include "AngryCubeLevel.h"

#include "game/objects/catapult/Catapult.h"


AngryCubeLevel::AngryCubeLevel(std::string levelName)
    : Level(std::move(levelName))
{
}

std::shared_ptr<Catapult> AngryCubeLevel::GetCatapult() const
{
    return catapult;
}

void AngryCubeLevel::SetCatapult(std::shared_ptr<Catapult> newCatapult)
{
    catapult = newCatapult;
    scene.Add(catapult);
}

void AngryCubeLevel::SetFortification(std::shared_ptr<Fortification> newFortification)
{
    fortification = newFortification;
    scene.Add(fortification);
}

std::shared_ptr<Fortification> AngryCubeLevel::GetFortification() const
{
    return fortification;
}
