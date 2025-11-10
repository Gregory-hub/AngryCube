#include "pch.h"
#include "AngryCubeLevel.h"

#include "game/objects/catapult/Catapult.h"
#include "game/objects/fortifications/FortificationOfLevel1.h"


AngryCubeLevel::AngryCubeLevel(std::string levelName)
    : Level(std::move(levelName))
{
    scene.SetGroundHeight(200.0f);

    catapult = std::make_shared<Catapult>(&scene);
    catapult->GetTransform().Move(glm::vec2(-500.0f, scene.GetGround()->GetHeight()));
    scene.Add(catapult);

    fortification = std::make_shared<FortificationOfLevel1>(&scene);
    int height = 0.0f;
    if (scene.GetGround())
        height = scene.GetGround()->GetHeight();
    fortification->GetTransform().SetTranslation(glm::vec2(500.0f, height));
    scene.Add(fortification);
}

std::shared_ptr<Catapult> AngryCubeLevel::GetCatapult() const
{
    return catapult;
}

std::shared_ptr<Fortification> AngryCubeLevel::GetFortification() const
{
    return fortification;
}
