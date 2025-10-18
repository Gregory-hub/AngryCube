#include "Catapult.h"

#include "CatapultArm.h"
#include "Cube.h"
#include "imgui.h"
#include "engine/components/mesh/DefaultMeshes.h"
#include "engine/material/SolidColor.h"
#include "engine/utility/ImGuiDragFloatWithSetter.h"


int Catapult::id = 0;

Catapult::Catapult(Scene* parentScene)
	: GameObject(parentScene, 100.0f)
{
    name = "Catapult " + std::to_string(id++);

	glm::vec4 color = glm::vec4(0.55, 0.59, 0.3, 1.0f);
	auto material = std::make_shared<SolidColor>(color);

	float woodWidth = 0.1f;
	std::shared_ptr<Cube> platform = std::make_shared<Cube>(scene);
	platform->GetTransform().SetScale(glm::vec2(1.8f, woodWidth * 2.0f));

	std::shared_ptr<Cube> frameUp = std::make_shared<Cube>(scene);
	frameUp->GetTransform().SetScale(glm::vec2(woodWidth * 2.0f, 1.0f));
	frameUp->GetTransform().SetTranslation(glm::vec2(
		platform->GetCollisionMesh()->GetWidth() * 0.25f,
		frameUp->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> frameLeft = std::make_shared<Cube>(scene);
	frameLeft->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameLeft->GetTransform().SetRotation(-30.0f);
	frameLeft->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x - platform->GetCollisionMesh()->GetWidth() * 0.3f,
		frameLeft->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> frameRight = std::make_shared<Cube>(scene);
	frameRight->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameRight->GetTransform().SetRotation(30.0f);
	frameRight->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x + platform->GetCollisionMesh()->GetWidth() * 0.3f,
		frameRight->GetCollisionMesh()->GetHeight() * 0.5f
	));
	
	arm = std::make_shared<CatapultArm>(scene);
	arm->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x - 10.0f,
		0.0f + 10.0f
	));
	arm->SetArmScale(glm::vec2(1.0f, woodWidth));
	arm->SetProgress(0.0f);

	std::shared_ptr<Cube> stopper = std::make_shared<Cube>(scene);
	stopper->GetTransform().SetScale(glm::vec2(woodWidth * 2.0f, woodWidth));
	stopper->GetTransform().SetRotation(-arm->GetMaxAngle());
	stopper->GetTransform().SetTranslation(glm::vec2(
		-5.0f,
		frameUp->GetCollisionMesh()->GetHeight() * 0.62f
	));
	
	AttachChild(platform);
	AttachChild(frameUp);
	AttachChild(frameLeft);
	AttachChild(frameRight);
	AttachChild(stopper);
	AttachChild(arm);

	for (auto& child : children)
	{
		for (auto& mesh : child->GetMeshes())
			mesh->SetMaterial(material);
	}
	arm->SetMaterial(material);

	std::shared_ptr<Cube> projectile = std::make_shared<Cube>(scene, 5.0f);
	projectile->GetTransform().SetScale(glm::vec2(0.2f, 0.2f));
	arm->LoadProjectile(projectile);

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

void Catapult::Release()
{
	arm->Release();
}

void Catapult::Cock()
{
	arm->Cock();
}

void Catapult::Update(float deltaTime)
{
}

void Catapult::ShowDebugControls()
{
    GameObject::ShowDebugControls();
    ImGui::DragFloatWithSetter("Progress", this->arm.get(), &CatapultArm::GetProgress, &CatapultArm::SetProgress, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloatWithSetter("Arm mass", this->arm.get(), &CatapultArm::GetArmMass, &CatapultArm::SetArmMass, 0.1f, 0.0f, 1000.0f);
	ImGui::DragFloatWithSetter("Spring k", this->arm.get(), &CatapultArm::GetK, &CatapultArm::SetK, 1.0f, 0.0f, 10000.0f);
    if (ImGui::Button("Release"))
        Release();
	ImGui::SameLine(0);
    if (ImGui::Button("Cock"))
        Cock();
}
