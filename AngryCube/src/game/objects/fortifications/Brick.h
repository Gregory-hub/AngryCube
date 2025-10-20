#pragma once
#include <memory>

#include "game/interfaces/IDestructable.h"

#include "game/objects/Cube.h"


class Brick : public Cube, public IDestructable, public std::enable_shared_from_this<Brick>
{
private:
	static unsigned int id;

public:
	Brick(Scene* parentScene, float mass = 1.0f);

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

	void Destroy();

	void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;
};

