#include "Catapult.h"

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
	
	AttachChild(platform);
	AttachChild(frameUp);
	AttachChild(frameLeft);
	AttachChild(frameRight);

	collisionMesh = std::make_unique<CollisionMesh>(std::make_unique<CubeMesh>());

	GetPhysics().Enable();
	GetCollision().Enable();
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

void Catapult::ShowDebugControls(glm::vec2 pos)
{
	//ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
	//ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Begin(name.c_str(), nullptr);
	GetTransform().ShowDebugControls();
	if (ImGui::Button("Physics"))
	{
		if (GetPhysics().Enabled())
			GetPhysics().Disable();
		else
			GetPhysics().Enable();
	}
	ImGui::End();
}

