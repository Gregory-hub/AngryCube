#include "pch.h"
#include "LevelSaveManager.h"

#include "engine/utility/jsonSerialization.h"
#include "engine/utility/Logger.h"


void LevelSaveManager::SaveLevel(std::shared_ptr<AngryCubeLevel> level, int index)
{
    using json = nlohmann::json;

    if (level->GetName().empty())
        throw std::invalid_argument("Level name is empty");

    if (level->GetName() == levelArrayFilename)
    {
        Logger::Log(LogLevel::Error, "Invalid level name");
        return;
    }

    json jsonResult;
    jsonResult["catapult"] = level->GetCatapult()->Serialize();
    jsonResult["fortification"] = level->GetFortification()->Serialize();

    std::filesystem::create_directories(folderPath);
    std::ofstream outFile(GetPath(level->GetName()));
    if (!outFile.is_open())
    {
        Logger::Log(LogLevel::Warning, "Cannot open " + GetPath(level->GetName()));
        return;
    }
    outFile << std::setw(4) << jsonResult << '\n';
    outFile.close();

    RegisterLevel(level->GetName(), index);
}

int LevelSaveManager::GetLevelCount()
{
    using json = nlohmann::json;

    std::ifstream inFile(GetPath(levelArrayFilename));
    if (!inFile.is_open())
        return 0;

    json levelArray = json::parse(inFile);

    inFile.close();

    if (levelArray.is_null() || !levelArray.is_array())
        return 0;
    return levelArray.size();
}

std::string LevelSaveManager::GetPath(const std::string& levelName)
{
    return folderPath + levelName + ".json";
}

void LevelSaveManager::RegisterLevel(const std::string& levelName, int index)
{
    using json = nlohmann::json;

    if (levelName.empty())
        throw std::invalid_argument("Level name is empty");

    json levelNames;

    std::filesystem::create_directories(folderPath);
    std::ifstream inFile(GetPath(levelArrayFilename));
    if (inFile.is_open())
        levelNames = json::parse(inFile);
    inFile.close();

    std::cout << std::setw(4) << levelNames << '\n';

    for (auto it = levelNames.begin(); it != levelNames.end();)
    {
        if (*it == levelName)
            it = levelNames.erase(it);
        else
            it++;
    }

    if (index >= levelNames.size() || index < 0)
        levelNames.push_back(levelName);
    else
        levelNames.insert(levelNames.begin() + index, levelName);

    std::ofstream outFile(GetPath(levelArrayFilename), std::ios::trunc);
    outFile << std::setw(4) << levelNames << '\n';
    outFile.close();
}

std::shared_ptr<AngryCubeLevel> LevelSaveManager::LoadLevel(const std::string& levelName)
{
    using json = nlohmann::json;

    if (levelName.empty())
        throw std::invalid_argument("Level name is empty");

    std::ifstream inFile(GetPath(levelName));
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
