#include "pch.h"
#include "Level.h"


const std::string& Level::GetName() const
{
	return name;
}

Level::Level(std::string levelName)
	: name(std::move(levelName))
{
	scene.SetGroundHeight(200.0f);
}

Scene& Level::GetScene()
{
	return scene;
}

void Level::Update(float deltaTime)
{
	scene.Update(deltaTime);
}
