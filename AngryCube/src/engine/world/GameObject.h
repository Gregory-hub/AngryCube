#pragma once
#include <string>
#include <memory>

#include "engine/components/physics/Physics.h"
#include "engine/components/transform/Transform.h"
#include "engine/components/mesh/Mesh.h"


class GameObject
{
protected:
	std::string name;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Physics> physics;

public:
	GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Transform> transform);
	GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Transform> transform, std::shared_ptr<Physics> physics);
	virtual ~GameObject() = default;

	GameObject(const GameObject& other) = default;
	GameObject& operator= (const GameObject& other) = default;

	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator= (GameObject&& other) noexcept = default;

	virtual std::shared_ptr<GameObject> Clone() const = 0;
	virtual std::shared_ptr<GameObject> MoveClone() = 0;

	virtual glm::vec2 GetLowestPoint() const = 0;
	virtual float GetHeight() const = 0;
	virtual float GetWidth() const = 0;

	const std::string& GetName() const;
	std::shared_ptr<Mesh>& GetMesh();
	std::shared_ptr<Transform>& GetTransform();
	std::shared_ptr<Physics>& GetPhysics();

	virtual void Update(float deltaTime) = 0;

	virtual void ShowDebugControls(glm::vec2 pos) { }
};

