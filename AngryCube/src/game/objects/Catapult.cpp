#include "Catapult.h"

#include "CatapultArm.h"
#include "Cube.h"
#include "imgui.h"
#include "engine/components/mesh/DefaultMeshes.h"


int Catapult::id = 0;

Catapult::Catapult()
	: GameObject()
{
    name = "Catapult " + std::to_string(id++);

	float woodWidth = 0.1f;
	std::shared_ptr<Cube> platform = std::make_shared<Cube>();
	platform->GetTransform().SetScale(glm::vec2(1.8f, woodWidth * 2.0f));

	std::shared_ptr<Cube> frameUp = std::make_shared<Cube>();
	frameUp->GetTransform().SetScale(glm::vec2(woodWidth * 2.0f, 1.0f));
	frameUp->GetTransform().SetTranslation(glm::vec2(
		platform->GetCollisionMesh()->GetWidth() * 0.25f,
		frameUp->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> frameLeft = std::make_shared<Cube>();
	frameLeft->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameLeft->GetTransform().SetRotation(-30.0f);
	frameLeft->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x - platform->GetCollisionMesh()->GetWidth() * 0.3f,
		frameLeft->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> frameRight = std::make_shared<Cube>();
	frameRight->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameRight->GetTransform().SetRotation(30.0f);
	frameRight->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x + platform->GetCollisionMesh()->GetWidth() * 0.3f,
		frameRight->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> stopper = std::make_shared<Cube>();
	stopper->GetTransform().SetScale(glm::vec2(woodWidth * 2.0f, woodWidth));
	stopper->GetTransform().SetRotation(frameLeft->GetTransform().GetRotation() - 45.0f);
	stopper->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x - platform->GetCollisionMesh()->GetWidth() * 0.15f,
		frameUp->GetCollisionMesh()->GetHeight() * 0.85f
	));

	std::shared_ptr<CatapultArm> arm = std::make_shared<CatapultArm>();
	arm->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x - 10.0f,
		0.0f + 10.0f
	));
	arm->SetArmScale(glm::vec2(1.0f, woodWidth));
	arm->SetProgress(0.0f);
	
	AttachChild(platform);
	AttachChild(frameUp);
	AttachChild(frameLeft);
	AttachChild(frameRight);
	AttachChild(stopper);
	AttachChild(arm);

	collisionMesh = std::make_unique<CollisionMesh>(std::make_unique<CubeMesh>());

	GetPhysics().Disable();
	GetCollision().Disable();
}

std::shared_ptr<GameObject> Catapult::Clone() const
{
    return std::make_shared<Catapult>(*this);
}

std::shared_ptr<GameObject> Catapult::MoveClone()
{
    return std::make_shared<Catapult>(std::move(*this));
}

void Catapult::Update(float deltaTime)
{
}

void Catapult::ShowDebugControls()
{
	GetTransform().ShowDebugControls();
}
