#include "FlatGround.h"


unsigned FlatGround::id = 0;

FlatGround::FlatGround(Scene* parentScene, float height)
	: Cube(parentScene, 0.0f), height(height)
{
	name = "FlatGround " + std::to_string(id++);

	GetTransform().SetScale(glm::vec2(10.0f, height / 100.0f));
	GetTransform().SetTranslation(glm::vec2(500.0f, height / 2.0f));

	GetPhysics().Disable();
	GetCollision().Enable();
}

float FlatGround::GetHeight() const
{
	return height;
}

void FlatGround::SetHeight(float newHeight)
{
	height = newHeight;
	GetTransform().SetScale(glm::vec2(1000.0f, height / 100.0f));
	GetTransform().SetTranslation(glm::vec2(500.0f, height / 2.0f));
}
