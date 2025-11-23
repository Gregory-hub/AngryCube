#include "pch.h"
#include "Brick.h"

#include "Fortification.h"
#include "engine/utility/ImGuiDragFloatWithSetter.h"
#include "engine/utility/jsonParsers.h"
#include "game/constants.h"
#include "game/interfaces/IProjectile.h"


int Brick::id = 0;

Brick::Brick(Scene* parentScene, float mass)
	: Cube(parentScene, mass)
{
	name = "Brick " + std::to_string(id++);
    GetPhysics().Enable();
    GetCollision().Enable();
}

std::shared_ptr<GameObject> Brick::Clone() const
{
	return std::make_shared<Brick>(*this);
}

std::shared_ptr<GameObject> Brick::MoveClone()
{
	return std::make_shared<Brick>(std::move(*this));
}

void Brick::Destroy()
{
	if (auto parentFortification = dynamic_cast<IDestructableContainer*>(parent))
		parentFortification->AddToDestructionQueue(shared_from_this());
}

nlohmann::json Brick::Serialize()
{
	using nlohmann::json;

	json jsonBrick;
	glm::vec2 pos = GetTransform().GetTranslation();
	glm::vec2 scale = GetTransform().GetScale();
	float mass = GetPhysics().GetMass();
	jsonBrick["pos"] = { pos.x, pos.y };
	jsonBrick["scale"] = { scale.x, scale.y };
	jsonBrick["mass"] = mass;
	return jsonBrick;
}

void Brick::Deserialize(const nlohmann::json& jsonBrick)
{
	bool ok = true;
	if (auto value = parseFromJson<glm::vec2>(jsonBrick, "pos"))
	{
		glm::vec2 pos = *value;
		GetTransform().SetTranslation(pos);
	}
	else
	{
		ok = false;
	}
	if (auto value = parseFromJson<glm::vec2>(jsonBrick, "scale"))
	{
		glm::vec2 scale = *value;
		GetTransform().SetScale(scale);
	}
	else
	{
		ok = false;
	}
	if (auto value = parseFromJson<float>(jsonBrick, "mass"))
	{
		float mass = *value;
		GetPhysics().SetMass(mass);
	}
	else
	{
		ok = false;
	}
	if (!ok)
	{
		// State of object is not broken so log and do nothing
		Logger::Log(LogLevel::Warning, "Failed to deserialize brick");
	}
}

void Brick::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
	if (std::dynamic_pointer_cast<IProjectile>(other))
		OnProjectileHit(other);
	else
		GetCollision().ResolveCollision(other);
}

void Brick::ShowDebugControls()
{
	Cube::ShowDebugControls();
	
	ImGui::DragFloatWithSetter("Mass",
		[this]() { return GetPhysics().GetMass(); },
		[this](float value) { GetPhysics().SetMass(value); },
		1.0f, 0.0f, 500.0f);
	
	if (ImGui::Button("Destroy"))
	{
        if (auto fort = dynamic_cast<Fortification*>(GetParent()))
            fort->SetWinGameEnabled(false);
		Destroy();
	}
}

void Brick::OnProjectileHit(const std::shared_ptr<GameObject>& projectile)
{
	if (glm::length(projectile->GetPhysics().GetVelocity()) >= VELOCITY_BREAK_BRICK_THRESHOLD)
		Destroy();
	else
		GetCollision().ResolveCollision(projectile);
}
