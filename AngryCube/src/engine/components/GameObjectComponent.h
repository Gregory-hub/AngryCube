#pragma once
class GameObjectComponent
{
public:
	virtual ~GameObjectComponent() = 0;
};

inline GameObjectComponent::~GameObjectComponent() = default;

