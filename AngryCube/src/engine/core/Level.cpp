#include "Level.h"


const Scene& Level::GetScene() const
{
	return scene;
}

void Level::Update(float deltaTime)
{
	scene.Update(deltaTime);
}
