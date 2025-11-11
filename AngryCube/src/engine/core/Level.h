#pragma once

#include "engine/world/Scene.h"


class Level
{
protected:
	std::string name;

public:
	const std::string& GetName() const;

protected:
	Scene scene;

public:
	Level(std::string levelName);
	virtual ~Level() = default;

	Level(const Level&) = default;
	Level& operator= (const Level&) = default;

	Level(Level&&) = default;
	Level& operator= (Level&&) = default;

	Scene& GetScene();

	virtual void Update(float deltaTime);
};
