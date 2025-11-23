#pragma once
#include <engine/world/GameObject.h>


class IProjectile
{
public:
	virtual void MarkAsLast() = 0;
	
private:
	virtual void OnTargetHit(std::shared_ptr<GameObject> target) = 0;
};
