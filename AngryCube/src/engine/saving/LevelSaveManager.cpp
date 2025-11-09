#include "pch.h"
#include "LevelSaveManager.h"

void LevelSaveManager::Save(std::shared_ptr<Level> level)
{
    json j = { {"Basic", 13}, "Json saver", "Level manager" };
    Logger::Log(LogLevel::Info, j.dump());
}
