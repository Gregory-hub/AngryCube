#include "pch.h"
#include "Brick.h"

#include "Fortification.h"
#include "engine/utility/jsonSerialization.h"
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
	jsonBrick["pos"] = { pos.x, pos.y };
	jsonBrick["scale"] = { scale.x, scale.y };
	return jsonBrick;
}

void Brick::Deserialize(const nlohmann::json& jsonBrick)
{
    if (!jsonBrick.is_null() && !jsonBrick["pos"].is_null())
    {
	    glm::vec2 brickPos = jsonVec2ToVec2(jsonBrick["pos"]);
    	glm::vec2 brickScale = jsonVec2ToVec2(jsonBrick["scale"]);
    	GetTransform().SetTranslation(brickPos);
    	GetTransform().SetScale(brickScale);
    }
	else
		throw std::invalid_argument("Brick deserialization failed");
}

void Brick::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
	if (auto projectile = std::dynamic_pointer_cast<IProjectile>(other))
		Destroy();
	else
		GetCollision().ResolveCollision(other);
}
