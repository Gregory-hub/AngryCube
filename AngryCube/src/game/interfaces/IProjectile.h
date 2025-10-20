#pragma once
#include <engine/world/GameObject.h>


class IProjectile
{
	virtual void OnTargetHit(std::shared_ptr<GameObject> target) = 0;
};
