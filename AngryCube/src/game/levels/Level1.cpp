#include "Level1.h"

#include "game/objects/Catapult.h"
#include "game/objects/Cube.h"
#include "game/objects/CatapultArm.h"


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

    scene.SetGround(50.0f);

    std::shared_ptr<Catapult> catapult = std::make_shared<Catapult>();
    catapult->GetTransform().Move(glm::vec2(800.0f, 300.0f));
    scene.Add(catapult);
}
