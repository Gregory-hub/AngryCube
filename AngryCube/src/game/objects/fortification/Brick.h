#pragma once
#include <memory>

#include "engine/saving/ISerializable.h"
#include "game/interfaces/IDestructable.h"

#include "game/objects/Cube.h"


class Brick : public Cube, public IDestructable, public std::enable_shared_from_this<Brick>, public ISerializable
{
private:
	static int id;

public:
	Brick(Scene* parentScene, float mass = 1.0f);

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

	void Destroy();
	
	nlohmann::json Serialize() override;
	void Deserialize(const nlohmann::json& json) override;

	void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;
};

