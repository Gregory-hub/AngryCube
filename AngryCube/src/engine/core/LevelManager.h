#pragma once

#include "Level.h"


class LevelManager
{
private:
	const std::string fileExtension = ".lvl";
	
	std::vector<std::string> levelNames;
	unsigned int currentLevelIndex = -1;

public:
	void AppendLevelName(const std::string& levelName);
	void InsertLevelName(unsigned int index, const std::string& levelName);
	void RemoveLevelName(unsigned int index);

	unsigned int LevelCount() const;
	unsigned int CurrentLevelIndex() const;

	Level Load(const std::string& levelName) const;
	Level Load(unsigned int index) const;
	Level LoadNext() const;
	
	void Save(const std::shared_ptr<Level>& level, const std::string& levelName) const;

private:
	Level ReadLevelFile(const std::string& levelName) const;
	void WriteLevelToFile(const std::shared_ptr<Level>& level, const std::string& levelName) const;
};
