#pragma once
#include "engine/saving/LevelSaveManager.h"


class AngryCubeLevelSaveManager : public LevelSaveManager
{
private:
    const std::string folderPath = "levels/";
    const std::string levelArrayFilename = "_levels";
    const std::string catapultJsonName = "catapult";
    const std::string fortificationJsonName = "fortification";

public:
    void SaveLevel(std::shared_ptr<Level> level, int index = -1) const override;
    std::shared_ptr<Level> LoadLevel(const std::string& levelName) const override;
    std::shared_ptr<Level> LoadLevel(int index) const override;

    int GetLevelCount() const override;
    std::string GetPath(const std::string& levelName) const;

private:
    nlohmann::json ParseLevelArray() const;
    void RegisterLevel(const std::string& levelName, int index) const;
};
