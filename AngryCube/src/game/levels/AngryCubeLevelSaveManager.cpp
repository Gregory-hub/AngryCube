#include "pch.h"
#include "AngryCubeLevelSaveManager.h"

#include "engine/utility/jsonSerialization.h"
#include "engine/utility/Logger.h"


void AngryCubeLevelSaveManager::SaveLevel(std::shared_ptr<Level> level, int index) const
{
    using nlohmann::json;

    if (level->GetName().empty() || level->GetName() == levelArrayFilename)
    {
        Logger::Log(LogLevel::Error, "Invalid level name");
        return;
    }

    auto angryLevel = std::dynamic_pointer_cast<AngryCubeLevel>(level);
    if (!angryLevel)
    {
        Logger::Log(LogLevel::Error, "Invalid level type");
        return;
    }

    json jsonResult;
    jsonResult[catapultJsonName] = angryLevel->GetCatapult()->Serialize();
    jsonResult[fortificationJsonName] = angryLevel->GetFortification()->Serialize();

    std::filesystem::create_directories(folderPath);
    std::ofstream outFile(GetPath(angryLevel->GetName()));
    if (!outFile.is_open())
    {
        Logger::Log(LogLevel::Error, "Cannot open " + GetPath(angryLevel->GetName()));
        return;
    }
    outFile << std::setw(4) << jsonResult << '\n';
    outFile.close();

    RegisterLevel(angryLevel->GetName(), index);
}

int AngryCubeLevelSaveManager::GetLevelCount() const
{
    using nlohmann::json;

    std::ifstream inFile(GetPath(levelArrayFilename));
    if (!inFile.is_open())
        return 0;

    json levelArray = json::parse(inFile);

    inFile.close();

    if (levelArray.is_null() || !levelArray.is_array())
        return 0;
    return levelArray.size();
}

std::string AngryCubeLevelSaveManager::GetPath(const std::string& levelName) const
{
    return folderPath + levelName + ".json";
}

nlohmann::json AngryCubeLevelSaveManager::ParseLevelArray() const
{
    using nlohmann::json;

    std::filesystem::create_directories(folderPath);
    std::ifstream inFile(GetPath(levelArrayFilename));
    if (inFile.is_open())
        return json::parse(inFile);
    inFile.close();

    return json::array();
}

void AngryCubeLevelSaveManager::RegisterLevel(const std::string& levelName, int index) const
{
    using nlohmann::json;

    if (levelName.empty())
    {
        Logger::Log(LogLevel::Error, "Level name is empty");
        return;
    }

    json levelNames = ParseLevelArray();

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

std::shared_ptr<Level> AngryCubeLevelSaveManager::LoadLevel(const std::string& levelName) const
{
    using nlohmann::json;

    if (levelName.empty())
    {
        Logger::Log(LogLevel::Error, "Level name is empty");
        return nullptr;
    }

    std::ifstream inFile(GetPath(levelName));
    json jsonInput = json::parse(inFile);

    if (jsonInput.is_null())
    {
        Logger::Log(LogLevel::Error, "Level json file is empty");
        return nullptr;
    }

    if (!jsonInput.contains(catapultJsonName) || !jsonInput.contains(fortificationJsonName))
    {
        Logger::Log(LogLevel::Error, "Invalid level");
        return nullptr;
    }

    std::shared_ptr<AngryCubeLevel> level = std::make_shared<AngryCubeLevel>(levelName);

    json jsonCatapult = jsonInput[catapultJsonName];
    auto catapult = std::make_shared<Catapult>(&level->GetScene());
    catapult->Deserialize(jsonCatapult);
    level->SetCatapult(catapult);

    json jsonFortification = jsonInput[fortificationJsonName];
    auto fortification = std::make_shared<Fortification>(&level->GetScene());
    fortification->Deserialize(jsonFortification);
    level->SetFortification(fortification);

    return level;
}

std::shared_ptr<Level> AngryCubeLevelSaveManager::LoadLevel(int index) const
{
    using nlohmann::json;

    json levelNames = ParseLevelArray();

    if (index < 0 || index >= levelNames.size())
    {
        Logger::Log(LogLevel::Warning, "Invalid index for level");
        return nullptr;
    }

    std::string levelName = levelNames[index].get<std::string>();
    return LoadLevel(levelName);
}
