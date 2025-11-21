#pragma once

#include "Level.h"
#include "engine/saving/LevelSaveManager.h"


class LevelManager
{
private:
	std::shared_ptr<LevelSaveManager> levelSaveManager;
	int currentLevelIndex = -1;

	std::shared_ptr<Level> activeLevel;

public:
	LevelManager(std::shared_ptr<LevelSaveManager> saveManager);

	int GetCurrentLevelIndex() const;
	int GetLevelCount() const;

	std::shared_ptr<Level> LoadFirstLevel();
	std::shared_ptr<Level> Load(int index);
	std::shared_ptr<Level> Load(const std::string& levelName);
	std::shared_ptr<Level> LoadNext();

	void Save(const std::shared_ptr<Level>& level, int index = -1) const;
	void SaveAsLast(const std::shared_ptr<Level>& level) const;
	
	const std::shared_ptr<Level>& GetActiveLevel();

private:
	void SetActiveLevel(const std::shared_ptr<Level>& level);
};
