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

Level LevelManager::Load(const std::string& levelName) const
{
    return ReadLevelFile(levelName);
}

Level LevelManager::Load(int index) const
{
    return ReadLevelFile(levelNames[index]);
}

Level LevelManager::LoadNext() const
{
    return Level();
}

void LevelManager::Save(const std::shared_ptr<Level>& level, const std::string& levelName) const
{
    WriteLevelToFile(level, levelName);
}

Level LevelManager::ReadLevelFile(const std::string& levelName) const
{
    std::string filename = levelName + fileExtension;
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        Logger::Log(LogLevel::Error, std::string("file not open (") + filename + ")");
        return Level();
    }

    char buffer[sizeof(float)];
    file.read(buffer, sizeof(float));
    
    float groundHeight = *reinterpret_cast<float*>(buffer);

    file.close();
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
