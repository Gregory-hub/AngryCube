#pragma once
#include "json.hpp"

#include "game/levels/AngryCubeLevel.h"


using json = nlohmann::json;


class LevelSaveManager
{
private:
    // inline static std::string folderPath = "";
    inline static std::string folderPath = "levels/";

public:
    LevelSaveManager() = delete;
    LevelSaveManager(const LevelSaveManager&) = delete;
    LevelSaveManager& operator= (const LevelSaveManager&) = delete;
    LevelSaveManager(LevelSaveManager&&) = delete;
    LevelSaveManager& operator= (LevelSaveManager&&) = delete;

    static void SaveLevel(std::shared_ptr<AngryCubeLevel> level);
};
