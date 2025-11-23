#include "pch.h"
#include "LevelManager.h"

#include <utility>

#include "Game.h"
#include "engine/utility/Logger.h"


LevelManager::LevelManager(std::unique_ptr<LevelSaveManager> saveManager)
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

std::shared_ptr<Level> LevelManager::Load(int index)
{
    if (index >= 0 && index < levelSaveManager->GetLevelCount())
    {
        currentLevelIndex = index;
    }
    else
    {
        Logger::Log(LogLevel::Error, "Level manager load invalid index");
        currentLevelIndex = -1;
        return nullptr;
    }

    if (std::shared_ptr<Level> level = levelSaveManager->LoadLevel(currentLevelIndex))
    {
        LoadNextFrame(level);
        currentLevelIndex = levelSaveManager->GetLevelIndex(level->GetName());
        return activeLevel;
    }
    else
    {
        Logger::Log(LogLevel::Error, "Level manager load failed");
        currentLevelIndex = -1;
        return nullptr;
    }
}

std::shared_ptr<Level> LevelManager::Load(const std::string& levelName)
{
    return Load(levelSaveManager->GetLevelIndex(levelName));
}

std::shared_ptr<Level> LevelManager::LoadFirstLevel()
{
    currentLevelIndex = 0;
    return Load(currentLevelIndex);
}

std::shared_ptr<Level> LevelManager::LoadNext()
{
    return Load(++currentLevelIndex);
}

void LevelManager::Update()
{
    if (levelToLoad)
    {
        SetActiveLevel(levelToLoad);
        levelToLoad = nullptr;
    }
}

void LevelManager::Save(const std::shared_ptr<Level>& level, int index) const
{
    levelSaveManager->SaveLevel(level, index);
}

void LevelManager::SaveAsLast(const std::shared_ptr<Level>& level) const
{
    Save(level);
}

const std::shared_ptr<Level>& LevelManager::GetActiveLevel()
{
    return activeLevel;
}

void LevelManager::SetActiveLevel(const std::shared_ptr<Level>& level)
{
    activeLevel = level;
}

void LevelManager::LoadNextFrame(std::shared_ptr<Level> level)
{
    levelToLoad = std::move(level);
}
