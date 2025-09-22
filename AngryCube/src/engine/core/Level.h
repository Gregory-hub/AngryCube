#pragma once

#include "engine/world/Scene.h"


class Level
{
protected:
	Scene scene;

public:
	Level() = default;
	virtual ~Level() = default;

	Level(const Level&) = default;
	Level& operator= (const Level&) = default;

	Level(Level&&) = default;
	Level& operator= (Level&&) = default;

	const Scene& GetScene() const;

	virtual void Update(float deltaTime);
};

