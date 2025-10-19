#include "pch.h"
#include "Catapult.h"

#include <stack>

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
	platform->GetTransform().SetScale(glm::vec2(2.0f, woodWidth * 2.0f));
	platform->GetTransform().SetTranslation(glm::vec2(0.0f, platform->GetCollisionMesh()->GetHeight() / 2.0f));

	std::shared_ptr<Cube> frameUp = std::make_shared<Cube>(scene);
	frameUp->GetTransform().SetScale(glm::vec2(woodWidth * 2.0f, 1.0f));
	frameUp->GetTransform().SetTranslation(glm::vec2(
		platform->GetCollisionMesh()->GetWidth() * 0.15f,
		frameUp->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> frameLeft = std::make_shared<Cube>(scene);
	frameLeft->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameLeft->GetTransform().SetRotation(-30.0f);
	frameLeft->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x - platform->GetCollisionMesh()->GetWidth() * 0.1f,
		frameLeft->GetCollisionMesh()->GetHeight() * 0.5f
	));

	std::shared_ptr<Cube> frameRight = std::make_shared<Cube>(scene);
	frameRight->GetTransform().SetScale(glm::vec2(woodWidth, 1.0f));
	frameRight->GetTransform().SetRotation(30.0f);
	frameRight->GetTransform().SetTranslation(glm::vec2(
		frameUp->GetTransform().GetTranslation().x + platform->GetCollisionMesh()->GetWidth() * 0.1f,
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
	stopper->GetTransform().SetRotation(-frameLeft->GetTransform().GetRotation() - arm->GetMaxAngle());
	stopper->GetTransform().SetTranslation(glm::vec2(0.0f, -5.0f));

	frameLeft->AttachChild(stopper);
	
	AttachChild(platform);
	AttachChild(frameUp);
	AttachChild(frameLeft);
	AttachChild(frameRight);
	AttachChild(arm);

	SetMaterial(material);

	std::shared_ptr<Cube> projectile = std::make_shared<Cube>(scene, 50.0f);
	projectile->GetTransform().SetScale(glm::vec2(0.2f, 0.2f));
	arm->LoadProjectile(projectile);

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

void Catapult::SetMaterial(const std::shared_ptr<Material>& material)
{
    std::stack<GameObject*> s;
    s.push(this);
    while (!s.empty())
    {
        GameObject* child = s.top();
        s.pop();

		for (auto& mesh : child->GetMeshes())
			mesh->SetMaterial(material);

        for (const auto& c : child->GetChildren())
            s.push(c.get());
    }
}
