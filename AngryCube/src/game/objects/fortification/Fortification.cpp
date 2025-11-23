#include "pch.h"
#include "Fortification.h"

#include "Brick.h"
#include "engine/core/Game.h"
#include "engine/utility/jsonParsers.h"
#include "engine/world/Scene.h"


int Fortification::id = 0;

Fortification::Fortification(Scene* parentScene)
    : GameObject(parentScene, 0.0f)
{
    name = "Fortification " + std::to_string(id++);
}

Fortification::Fortification(const Fortification& other)
    : GameObject(other), physicsEnabled(other.physicsEnabled)
{
    name = "Fortification " + std::to_string(id++);
}

Fortification& Fortification::operator=(const Fortification& other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        name = "Fortification " + std::to_string(id++);
        physicsEnabled = other.physicsEnabled;
    }
    return *this;
}

Fortification::Fortification(Fortification&& other) noexcept
    : GameObject(std::move(other)),
    physicsEnabled(std::move(other.physicsEnabled)),
    brickCount(std::move(other.brickCount)),
    destructionQueue(std::move(other.destructionQueue))
{
    name = "Fortification " + std::to_string(id++);
}

Fortification& Fortification::operator=(Fortification&& other) noexcept
{
    if (this != &other)
    {
        GameObject::operator=(std::move(other));

        name = "Fortification " + std::to_string(id++);
        std::swap(physicsEnabled, other.physicsEnabled);
        std::swap(brickCount, other.brickCount);
        std::swap(destructionQueue, other.destructionQueue);
    }

    return *this;
}

std::shared_ptr<GameObject> Fortification::Clone() const
{
    return std::make_shared<Fortification>(*this);
}

std::shared_ptr<GameObject> Fortification::MoveClone()
{
    return std::make_shared<Fortification>(std::move(*this));
}

void Fortification::AttachChild(const std::shared_ptr<GameObject>& child, bool disablePhysics)
{
    if (auto brick = std::dynamic_pointer_cast<Brick>(child))
        brickCount++;
    GameObject::AttachChild(child, disablePhysics);
}

void Fortification::RemoveChild(const std::shared_ptr<GameObject>& child)
{
    if (auto brick = std::dynamic_pointer_cast<Brick>(child))
        brickCount--;
    GameObject::RemoveChild(child);
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

    bool ok = true;
    if (auto value = parseFromJson<glm::vec2>(jsonFortification, "pos"))
    {
        glm::vec2 pos = *value;
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
    {
        ok = false;
    }

    if (!ok)
    {
		// State of object is not broken so log and do nothing
		Logger::Log(LogLevel::Warning, "Failed to deserialize fortification");
    }
}

void Fortification::ToggleBricksPhysics()
{
    for (std::shared_ptr<GameObject> child : GetChildren())
    {
        if (auto brick = std::dynamic_pointer_cast<Brick>(child))
        {
            if (physicsEnabled)
            {
                brick->GetPhysics().Disable();
            }
            else
            {
                brick->GetPhysics().Enable();
            }
        }
    }
    physicsEnabled = !physicsEnabled;
}

void Fortification::ShowDebugControls()
{
    GameObject::ShowDebugControls();

    if (ImGui::Button("Add brick"))
    {
        auto brick = std::make_shared<Brick>(scene);
        AttachChild(brick, true);
    }
    ImGui::SameLine();
    if (ImGui::Button("Toggle bricks' physics"))
    {
        ToggleBricksPhysics();
    }
}

int Fortification::GetBrickCount() const
{
    return brickCount;
}

bool Fortification::GetWinGameEnabled() const
{
    return winGameEnabled;
}

void Fortification::SetWinGameEnabled(bool newWinGameEnabled)
{
    winGameEnabled = newWinGameEnabled;
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

    if (GetBrickCount() <= 0 && winGameEnabled)
        Game::GameLevelManager->LoadNext();
}
