#pragma once

#include <string>
#include <memory>

#include "components/physics/Physics.h"
#include "components/transform/Transform.h"
#include "engine/components/mesh/Mesh.h"


class GameObject
{
protected:
	std::string name;
	Mesh mesh;
	Transform transform;
	Physics physics;

public:
	GameObject(Mesh mesh, Transform transform);
	virtual ~GameObject() = default;

	GameObject(const GameObject& other) = default;
	GameObject& operator= (const GameObject& other) = default;

	GameObject(GameObject&& other) noexcept = default;
	GameObject& operator= (GameObject&& other) noexcept = default;

	virtual std::shared_ptr<GameObject> Clone() const = 0;
	virtual std::shared_ptr<GameObject> MoveClone() = 0;

	const std::string& GetName() const;
	Mesh& GetMesh();
	Transform& GetTransform();
	Physics& GetPhysics();

	virtual void Update(float deltaTime) = 0;

	virtual void ShowDebugControls(glm::vec2 pos) { }
};

