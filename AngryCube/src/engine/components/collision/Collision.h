#pragma once
#include <memory>

class GameObject;


class Collision
{
private:
	GameObject* parentObject;

public:
	Collision(GameObject* parentObject);
	bool IsColliding(const std::shared_ptr<GameObject>& other) const;
};

