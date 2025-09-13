#pragma once

#include <string>
#include <memory>

#include "engine/mesh/Mesh.h"
#include "engine/movement/Movement.h"


class GameObject
{
protected:
	std::string name;
	std::shared_ptr<Mesh> mesh = nullptr;
	std::shared_ptr<Movement> movement = nullptr;

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	GameObject(const GameObject& other) = default;
	GameObject& operator= (const GameObject& other) = default;

	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator= (GameObject&& other) noexcept = default;

	virtual std::shared_ptr<GameObject> Clone() const = 0;
	virtual std::shared_ptr<GameObject> MoveClone() = 0;

	const std::string& GetName() const;
	const std::shared_ptr<Mesh>& GetMesh();
	const std::shared_ptr<Movement>& GetMovement();

	virtual void Update(float deltaTime) = 0;

	virtual void ShowDebugControls(glm::vec2 pos) { };
};

