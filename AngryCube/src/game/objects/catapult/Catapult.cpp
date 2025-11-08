#include "pch.h"
#include "Catapult.h"

#include <stack>

#include "imgui.h"

#include "engine/components/mesh/DefaultMeshes.h"
#include "engine/materials/SolidColor.h"
#include "engine/utility/ImGuiDragFloatWithSetter.h"

#include "CatapultArm.h"
#include "game/objects/Cube.h"
#include <game/objects/projectiles/ProjectileCube.h>


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

	auto projectile = std::make_shared<ProjectileCube>(scene, 20.0f);
	projectile->GetTransform().SetScale(glm::vec2(0.2f, 0.2f));
	SetProjectileTemplate(projectile);
	Load();

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

std::shared_ptr<IProjectile> Catapult::GetProjectileTemplate() const
{
	return projectileTemplate;
}

void Catapult::SetProjectileTemplate(std::shared_ptr<IProjectile> newTemplate)
{
	projectileTemplate = newTemplate;
}

float Catapult::GetSpringTension() const
{
	return arm->GetK();
}

void Catapult::SetSpringTension(float newTension) const
{
	arm->SetK(newTension);
}

float Catapult::GetAngle() const
{
	return arm->GetMaxAngle();
}

void Catapult::SetAngle(float newAngle) const
{
	arm->SetMaxAngle(newAngle);
}

void Catapult::Load(std::shared_ptr<IProjectile> projectile)
{
	if (!projectile && projectileTemplate)
	{
		if (std::shared_ptr<GameObject> tmp = std::dynamic_pointer_cast<GameObject>(projectileTemplate))
			projectile = std::dynamic_pointer_cast<IProjectile>(tmp->Clone());
	}

	if (projectile)
		arm->LoadProjectile(projectile);

}

void Catapult::Release()
{
	arm->Release();
}

void Catapult::Cock()
{
	arm->Cock();
}

bool Catapult::ReadyToRelease() const
{
	return arm->GetArmMode() == CatapultArmMode::Cocked && arm->GetProjectile();
}

void Catapult::Update(float deltaTime)
{
	if (arm->GetArmMode() == CatapultArmMode::Cocked && !arm->GetProjectile())
		Load();
}

void Catapult::ShowDebugControls()
{
    GameObject::ShowDebugControls();
	
    ImGui::DragFloatWithSetter("Progress",
    	[this]() { return arm->GetProgress(); },
    	[this](float value) { arm->SetProgress(value); },
    	0.01f, 0.0f, 1.0f);
	
    ImGui::DragFloatWithSetter("Arm mass",
    	[this]() { return arm->GetArmMass(); },
    	[this](float value) { arm->SetArmMass(value); },
    	0.1f, 0.0f, 1000.0f);
	
	ImGui::DragFloatWithSetter("Spring k",
    	[this]() { return arm->GetK(); },
    	[this](float value) { arm->SetK(value); },
		1.0f, 0.0f, 10000.0f);
	
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
