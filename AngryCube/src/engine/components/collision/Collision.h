#pragma once
#include "engine/components/GameObjectComponent.h"


class Collision : public GameObjectComponent
{
protected:
    bool enabled = false;
    
public:
	Collision(GameObject* parent);
	~Collision() override = 0;

	Collision(const Collision& other) = default;
	Collision& operator= (const Collision& other) = default;

	Collision(Collision&& other) noexcept = default;
	Collision& operator= (Collision&& other) noexcept = default;
	
	virtual void Enable();
	virtual void Disable();
	virtual bool Enabled() const;
};

inline Collision::~Collision() = default;
