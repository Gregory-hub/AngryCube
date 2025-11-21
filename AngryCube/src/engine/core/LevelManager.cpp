#include "pch.h"
#include "LevelManager.h"

#include <utility>

#include "engine/utility/Logger.h"


LevelManager::LevelManager(std::shared_ptr<LevelSaveManager> saveManager)
    : levelSaveManager(std::move(saveManager))
{
    if (levelSaveManager == nullptr)
        Logger::Log(LogLevel::Error, "Level save manager cannot be nullptr");
}

int LevelManager::GetCurrentLevelIndex() const
{
    return currentLevelIndex;
}

int LevelManager::GetLevelCount() const
{
    return levelSaveManager->GetLevelCount();
}

std::shared_ptr<Level> LevelManager::Load(const std::string& levelName)
{
    return levelSaveManager->LoadLevel(levelName);
}

std::shared_ptr<Level> LevelManager::Load(int index)
{
    if (index >= 0 && index < levelSaveManager->GetLevelCount())
        currentLevelIndex = index;

    return levelSaveManager->LoadLevel(index);
}

std::shared_ptr<Level> LevelManager::LoadNext()
{
    int index = currentLevelIndex;
    if (currentLevelIndex + 1 >= 0 && currentLevelIndex + 1 < levelSaveManager->GetLevelCount())
        currentLevelIndex++;

    return levelSaveManager->LoadLevel(index + 1);
}

void LevelManager::Save(const std::shared_ptr<Level>& level, int index) const
{
    levelSaveManager->SaveLevel(level, index);
}

void LevelManager::SaveAsLast(const std::shared_ptr<Level>& level) const
{
    levelSaveManager->SaveLevel(level);
}
