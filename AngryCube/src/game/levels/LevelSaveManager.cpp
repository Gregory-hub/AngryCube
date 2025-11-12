#include "pch.h"
#include "LevelSaveManager.h"

#include "engine/utility/jsonSerialization.h"
#include "engine/utility/Logger.h"


void LevelSaveManager::SaveLevel(std::shared_ptr<AngryCubeLevel> level)
{
    using json = nlohmann::json;
    
    if (level->GetName().empty())
        throw std::invalid_argument("Level name is empty");

    json jsonResult;
    jsonResult["catapult"] = level->GetCatapult()->Serialize();
    jsonResult["fortification"] = level->GetFortification()->Serialize();

    std::filesystem::create_directories(folderPath);
    std::ofstream outFile(folderPath + level->GetName() + ".json");
    if (!outFile.is_open())
    {
        Logger::Log(LogLevel::Warning, "Cannot write level json file");
        return;
    }
    outFile << std::setw(4) << jsonResult << '\n';
    outFile.close();
}

std::shared_ptr<AngryCubeLevel> LevelSaveManager::LoadLevel(const std::string& levelName)
{
    using json = nlohmann::json;
    
    if (levelName.empty())
        throw std::invalid_argument("Level name is empty");

    std::ifstream inFile(folderPath + levelName + ".json");
    json jsonInput = json::parse(inFile);

    if (jsonInput.is_null())
        throw std::invalid_argument("Level json file is empty");

    std::shared_ptr<AngryCubeLevel> level = std::make_shared<AngryCubeLevel>(levelName);

    json jsonCatapult = jsonInput["catapult"];
    auto catapult = std::make_shared<Catapult>(&level->GetScene());
    catapult->Deserialize(jsonCatapult);
    level->SetCatapult(catapult);

    json jsonFortification = jsonInput["fortification"];
    auto fortification = std::make_shared<Fortification>(&level->GetScene());
    fortification->Deserialize(jsonFortification);
    level->SetFortification(fortification);

    return level;
}
