#pragma once
#include "json.hpp"

#include "game/levels/AngryCubeLevel.h"


class LevelSaveManager
{
private:
    inline static std::string folderPath = "levels/";
    inline static std::string levelArrayFilename = "_levels";

public:
    LevelSaveManager() = delete;
    LevelSaveManager(const LevelSaveManager&) = delete;
    LevelSaveManager& operator= (const LevelSaveManager&) = delete;
    LevelSaveManager(LevelSaveManager&&) = delete;
    LevelSaveManager& operator= (LevelSaveManager&&) = delete;

    static void SaveLevel(std::shared_ptr<AngryCubeLevel> level, int index = -1);
    static std::shared_ptr<AngryCubeLevel> LoadLevel(const std::string& levelName);

    static int GetLevelCount();
    static std::string GetPath(const std::string& levelName);

private:
    static void RegisterLevel(const std::string& levelName, int index);
};
