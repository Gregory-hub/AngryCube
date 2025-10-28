#include "pch.h"
#include "Brick.h"

#include "Fortification.h"
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

void Brick::OnCollisionStart(const std::shared_ptr<GameObject>& other)
{
	if (auto projectile = std::dynamic_pointer_cast<IProjectile>(other))
		Destroy();
	else
		GetCollision().ResolveCollision(other);
}
