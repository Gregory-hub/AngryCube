#include "Catapult.h"

#include "Cube.h"


Catapult::Catapult()
{
	float woodWidth = 0.1f;
	std::shared_ptr<Cube> platform = std::make_shared<Cube>();
	platform->GetTransform().SetScale(glm::vec2(1.8f, woodWidth * 2.0f));

	std::shared_ptr<Cube> frameUp = std::make_shared<Cube>();
	frameUp->GetTransform().SetScale(glm::vec2(woodWidth * 2.0f, 1.0f));
	frameUp->GetTransform().SetTranslation(glm::vec2(platform->GetWidth() * 0.25f, frameUp->GetHeight() * 0.5f));

	std::shared_ptr<Cube> frameLeft = std::make_shared<Cube>();
	frameLeft->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameLeft->GetTransform().SetRotation(-20.0f);
	frameLeft->GetTransform().SetTranslation(glm::vec2(frameUp->GetTransform().GetTranslation().x - platform->GetWidth() * 0.1f, frameLeft->GetHeight() * 0.5f));

	std::shared_ptr<Cube> frameRight = std::make_shared<Cube>();
	frameRight->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameRight->GetTransform().SetRotation(20.0f);
	frameRight->GetTransform().SetTranslation(glm::vec2(frameUp->GetTransform().GetTranslation().x + platform->GetWidth() * 0.1f, frameRight->GetHeight() * 0.5f));
	
	Add(platform);
	Add(frameUp);
	Add(frameLeft);
	Add(frameRight);
}

