#include "pch.h"
#include "Fortification.h"

#include "Brick.h"
#include "engine/utility/jsonSerialization.h"
#include "engine/world/Scene.h"


int Fortification::id = 0;

Fortification::Fortification(Scene* parentScene)
    : GameObject(parentScene, 0.0f)
{
    name = "Fortification " + std::to_string(id++);
}

std::shared_ptr<GameObject> Fortification::Clone() const
{
    return std::make_shared<Fortification>(*this);
}

std::shared_ptr<GameObject> Fortification::MoveClone()
{
    return std::make_shared<Fortification>(std::move(*this));
}

void Fortification::Update(float deltaTime)
{
    DestroyObjectsInQueue();
}

void Fortification::AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed)
{
    destructionQueue.push(destroyed);
}

void Fortification::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
}

nlohmann::json Fortification::Serialize()
{
    using nlohmann::json;

    json jsonFortification;
    glm::vec2 posFort = GetTransform().GetTranslation();

    json jsonFortBricks;
    for (const auto& child : GetChildren())
    {
        if (const auto& brick = std::dynamic_pointer_cast<Brick>(child))
        {
            json jsonBrick = brick->Serialize();
            jsonFortBricks.push_back(jsonBrick);
        }
    }

    jsonFortification["pos"] = { posFort.x, posFort.y };
    jsonFortification["bricks"] = jsonFortBricks;
    return jsonFortification;
}

void Fortification::Deserialize(const nlohmann::json& jsonFortification)
{
    using nlohmann::json;

    if (!jsonFortification.is_null() && !jsonFortification["pos"].is_null())
     {
         glm::vec2 pos = jsonVec2ToVec2(jsonFortification["pos"]);
         GetTransform().SetTranslation(pos);

         json jsonFortBricks = jsonFortification["bricks"];
         for (const auto& jsonBrick : jsonFortBricks)
         {
             auto brick = std::make_shared<Brick>(scene);
             brick->Deserialize(jsonBrick);
             AttachChild(brick, false);
         }
     }
     else
         throw std::invalid_argument("Fortification deserialization failed");
}

void Fortification::DestroyObjectsInQueue()
{
    while (!destructionQueue.empty())
    {
        std::shared_ptr<IDestructable> destroyed = destructionQueue.front();
		destructionQueue.pop();

        if (auto object = std::dynamic_pointer_cast<GameObject>(destroyed))
        {
            RemoveChild(object);
            scene->Remove(object);
        }
    }
}
