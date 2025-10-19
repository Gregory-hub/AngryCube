#include "pch.h"
#include "Level1.h"

#include "game/objects/Catapult.h"
#include "game/objects/Cube.h"
#include "game/objects/fortifications/FortificationOfLevel1.h"


Level1::Level1()
{
    //std::shared_ptr<GameObject> cube = std::make_shared<Cube>(1.0f);
    //cube->GetTransform().SetTranslation({ 990.0f, 660.0f });
    //cube->GetTransform().SetScale({ 1.5f, 1.5f });

    //std::shared_ptr<GameObject> cube1 = std::make_shared<Cube>(10.0f);
    //cube1->GetTransform().SetTranslation({ 790.0f, 660.0f });

    //std::shared_ptr<GameObject> cube2 = std::make_shared<Cube>(100.0f);
    //cube2->GetTransform().SetTranslation({ 590.0f, 660.0f });
    //cube2->GetTransform().SetScale({ 0.5f, 0.5f });

    //scene.Add(cube);
    //scene.Add(cube1);
    //scene.Add(cube2);

    scene.SetGroundHeight(100.0f);

    std::shared_ptr<Catapult> catapult = std::make_shared<Catapult>(&scene);
    catapult->GetTransform().Move(glm::vec2(200.0f, 100.0f));
    scene.Add(catapult);

    std::shared_ptr<FortificationOfLevel1> fortification = std::make_shared<FortificationOfLevel1>(&scene);
    int height = 0.0f;
    if (scene.GetGround())
        height = scene.GetGround()->GetHeight();
    fortification->GetTransform().SetTranslation(glm::vec2(1000.0f, height));
    scene.Add(fortification);
}
