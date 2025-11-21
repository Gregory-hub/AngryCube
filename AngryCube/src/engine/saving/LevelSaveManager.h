#pragma once
#include "engine/core/Level.h"


// You should use subclass of this class to be able to save and load levels with default LevelManager 
class LevelSaveManager
{
public:
    virtual ~LevelSaveManager() = default;

    virtual void SaveLevel(std::shared_ptr<Level> level, int index = -1) const = 0;
    virtual std::shared_ptr<Level> LoadLevel(const std::string& levelName) const = 0;
    virtual std::shared_ptr<Level> LoadLevel(int index) const = 0;
    virtual int GetLevelCount() const = 0;
    virtual int GetLevelIndex(const std::string& levelName) const = 0;
};
