#include "pch.h"
#include "LevelSaveManager.h"

#include "engine/utility/Logger.h"
#include "game/objects/fortifications/Brick.h"


void LevelSaveManager::SaveLevel(std::shared_ptr<AngryCubeLevel> level)
{
    if (level->GetName().empty())
        throw std::invalid_argument("Level name is empty");

    json jsonCatapult;
    std::shared_ptr<Catapult> catapult = level->GetCatapult();
    glm::vec2 posCat = catapult->GetTransform().GetTranslation();
    jsonCatapult["pos"] = { posCat.x, posCat.y };

    json jsonFortification;
    std::shared_ptr<Fortification> fortification = level->GetFortification();
    glm::vec2 posFort = fortification->GetTransform().GetTranslation();
    jsonFortification["pos"] = { posFort.x, posFort.y };

    json jsonFortBricks;
    const auto& cubes = fortification->GetChildren();
    for (const auto& cube : cubes)
    {
        json jsonObj;
        glm::vec2 pos = cube->GetTransform().GetTranslation();
        glm::vec2 scale = cube->GetTransform().GetScale();
        jsonObj["pos"] = { pos.x, pos.y };
        jsonObj["scale"] = { scale.x, scale.y };
        jsonFortBricks.push_back(jsonObj);
    }
    jsonFortification["bricks"] = jsonFortBricks;

    json jsonResult;
    jsonResult["catapult"] = jsonCatapult;
    jsonResult["fortification"] = jsonFortification;

    std::filesystem::create_directories(folderPath);
    std::ofstream outFile(folderPath + level->GetName() + ".json");
    if (!outFile.is_open())
        Logger::Log(LogLevel::Warning, "Cannot write level json file");
    outFile << std::setw(4) << jsonResult << '\n';
    outFile.close();
}

std::shared_ptr<AngryCubeLevel> LevelSaveManager::LoadLevel(const std::string& levelName)
{
    if (levelName.empty())
        throw std::invalid_argument("Level name is empty");

    std::ifstream inFile(folderPath + levelName + ".json");
    json jsonInput = json::parse(inFile);

    if (jsonInput.is_null())
        throw std::invalid_argument("Level json file is empty");

    std::shared_ptr<AngryCubeLevel> level = std::make_shared<AngryCubeLevel>(levelName);

    json jsonCatapult = jsonInput["catapult"];
    if (!jsonCatapult.is_null() && !jsonCatapult["pos"].is_null())
    {
        auto catapult = std::make_shared<Catapult>(&level->GetScene());
        glm::vec2 pos = JsonVec2ToVec2(jsonCatapult["pos"]);
        catapult->GetTransform().SetTranslation(pos);
        level->SetCatapult(catapult);
    }
    else
        throw std::invalid_argument("Level json file is corrupted");

    json jsonFortification = jsonInput["fortification"];
    if (!jsonFortification.is_null() && !jsonFortification["pos"].is_null())
    {
        auto fortification = std::make_shared<Fortification>(&level->GetScene());
        glm::vec2 pos = JsonVec2ToVec2(jsonFortification["pos"]);
        fortification->GetTransform().SetTranslation(pos);

        json jsonFortBricks = jsonFortification["bricks"];
        for (const auto& jsonCube : jsonFortBricks)
        {
            glm::vec2 brickPos = JsonVec2ToVec2(jsonCube["pos"]);
            glm::vec2 brickScale = JsonVec2ToVec2(jsonCube["scale"]);
            auto brick = std::make_shared<Brick>(&level->GetScene());
            brick->GetTransform().SetTranslation(brickPos);
            brick->GetTransform().SetScale(brickScale);
            fortification->AttachChild(brick, false);
        }
        level->SetFortification(fortification);
    }
    else
        throw std::invalid_argument("Level json file is corrupted");

    return level;
}

glm::vec2 LevelSaveManager::JsonVec2ToVec2(const json& jsonVec2)
{
    if (!jsonVec2.is_null() && !jsonVec2[0].is_null() && !jsonVec2[1].is_null())
        return { jsonVec2[0].get<float>(), jsonVec2[1].get<float>() };
    else
        throw std::invalid_argument("Level json file is corrupted");
}
