#pragma once
#include "json.hpp"

#include "engine/core/Level.h"

using json = nlohmann::json;


class LevelSaveManager
{
public:
    LevelSaveManager() = delete;
    LevelSaveManager(const LevelSaveManager&) = delete;
    LevelSaveManager& operator() (const LevelSaveManager&) = delete;
    LevelSaveManager(LevelSaveManager&&) = delete;
    LevelSaveManager& operator() (LevelSaveManager&&) = delete;

    static void Save(std::shared_ptr<Level> level);

private:
};
