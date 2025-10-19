#include "pch.h"
#include "FlatGround.h"

#include "engine/material/SolidColor.h"


unsigned FlatGround::id = 0;

FlatGround::FlatGround(Scene* parentScene, float height)
	: Cube(parentScene, 0.0f), height(height)
{
	name = "FlatGround " + std::to_string(id++);

	glm::vec4 color(0.145f, 0.349f, 0.12f, 1.0f);

	for (auto& mesh : GetMeshes())
		mesh->SetMaterial(std::make_shared<SolidColor>(color));

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
