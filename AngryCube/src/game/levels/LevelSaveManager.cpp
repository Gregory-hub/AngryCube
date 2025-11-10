#include "pch.h"
#include "LevelSaveManager.h"

#include "engine/utility/Logger.h"


void LevelSaveManager::SaveLevel(std::shared_ptr<AngryCubeLevel> level)
{
    if (level->GetName().empty())
        return;

    json jsonCatapult;
    std::shared_ptr<Catapult> catapult = level->GetCatapult();
    glm::vec2 posCat = catapult->GetTransform().GetTranslation();
    jsonCatapult["pos"] = { posCat.x, posCat.y };

    json jsonFortification;
    std::shared_ptr<Fortification> fortification = level->GetFortification();
    glm::vec2 posFort = fortification->GetTransform().GetTranslation();
    jsonFortification["pos"] = { posFort.x, posFort.y };

    json jsonFortCubes;
    const auto& cubes = fortification->GetChildren();
    for (const auto& cube : cubes)
    {
        json jsonObj;
        glm::vec2 pos = cube->GetTransform().GetTranslation();
        glm::vec2 scale = cube->GetTransform().GetScale();
        jsonObj["pos"] = { pos.x, pos.y };
        jsonObj["scale"] = { scale.x, scale.y };
        jsonFortCubes.push_back(jsonObj);
    }
    jsonFortification["cubes"] = jsonFortCubes;

    json jsonResult;
    jsonResult["catapult"] = jsonCatapult;
    jsonResult["fortification"] = jsonFortification;

    std::filesystem::create_directories(folderPath);

    std::ofstream outFile(folderPath + level->GetName() + ".json");
    if (!outFile.is_open())
        Logger::Log(LogLevel::Warning, "Cannot write level json file");
    outFile << std::setw(4) << jsonResult << '\n';
    outFile.close();

    // Logger::Log(LogLevel::Info, jsonResult.dump());
}
