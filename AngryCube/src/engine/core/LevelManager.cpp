#include "pch.h"
#include "LevelManager.h"

#include <fstream>

#include "engine/utility/Logger.h"


void LevelManager::AppendLevelName(const std::string& levelName)
{
    levelNames.push_back(levelName);
}

void LevelManager::InsertLevelName(int index, const std::string& levelName)
{
    levelNames.insert(levelNames.begin() + index, levelName);
}

void LevelManager::RemoveLevelName(int index)
{
    levelNames.erase(levelNames.begin() + index);
}

int LevelManager::LevelCount() const
{
    return levelNames.size();
}

std::unique_ptr<Level> LevelManager::Load(const std::string& levelName) const
{
    return ReadLevelFile(levelName);
}

std::unique_ptr<Level> LevelManager::Load(int index) const
{
    return ReadLevelFile(levelNames[index]);
}

std::unique_ptr<Level> LevelManager::LoadNext() const
{
    return std::make_unique<Level>("");
}

void LevelManager::Save(const std::shared_ptr<Level>& level, const std::string& levelName) const
{
    WriteLevelToFile(level, levelName);
}

std::unique_ptr<Level> LevelManager::ReadLevelFile(const std::string& levelName) const
{
    std::string filename = levelName + fileExtension;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        Logger::Log(LogLevel::Error, std::string("file not open (") + filename + ")");
        return std::make_unique<Level>("");
    }

    char buffer[sizeof(float)];
    file.read(buffer, sizeof(float));
    
    float groundHeight = *reinterpret_cast<float*>(buffer);

    file.close();
    
    return std::make_unique<Level>("");
}

void LevelManager::WriteLevelToFile(const std::shared_ptr<Level>& level, const std::string& levelName) const
{
    std::string filename = levelName + fileExtension;
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        Logger::Log(LogLevel::Error, std::string("file not open (") + filename + ")");
        return;
    }

    const Scene& scene = level->GetScene();

    float groundHeight = scene.GetGround()->GetHeight();
    file.write(reinterpret_cast<const char*>(&groundHeight), sizeof(float));

    file.close();
}
