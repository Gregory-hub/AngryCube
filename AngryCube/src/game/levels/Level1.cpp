#include "pch.h"
#include "Level1.h"

#include "game/objects/catapult/Catapult.h"
#include "game/objects/Cube.h"
#include "game/objects/fortifications/FortificationOfLevel1.h"


Level1::Level1()
{
    scene.SetGroundHeight(100.0f);

    std::shared_ptr<Catapult> catapult = std::make_shared<Catapult>(&scene);
    catapult->GetTransform().Move(glm::vec2(200.0f, scene.GetGround()->GetHeight()));
    scene.Add(catapult);

    std::shared_ptr<FortificationOfLevel1> fortification = std::make_shared<FortificationOfLevel1>(&scene);
    int height = 0.0f;
    if (scene.GetGround())
        height = scene.GetGround()->GetHeight();
    fortification->GetTransform().SetTranslation(glm::vec2(1000.0f, height));
    scene.Add(fortification);
}
