#include "pch.h"
#include "Level.h"


const std::string& Level::GetName() const
{
	return name;
}

Level::Level(std::string levelName)
	: name(std::move(levelName))
{
}

const Scene& Level::GetScene() const
{
	return scene;
}

void Level::Update(float deltaTime)
{
	scene.Update(deltaTime);
}
