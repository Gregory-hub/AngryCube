#pragma once
#include <string>
#include <memory>

#include "engine/components/collision/Collision.h"
#include "engine/components/physics/Physics.h"
#include "engine/components/transform/Transform.h"
#include "engine/components/mesh/Mesh.h"


class GameObject
{
protected:
	std::string name;
	std::vector<std::shared_ptr<Mesh>> meshes;
	Transform transform;
	Physics physics;
	Collision collision;

public:
	GameObject();
	GameObject(float mass);
	virtual ~GameObject() = default;

	GameObject(const GameObject& other);
	GameObject& operator= (const GameObject& other);

	GameObject(GameObject&& other) noexcept;
	GameObject& operator= (GameObject&& other) noexcept;

	virtual std::shared_ptr<GameObject> Clone() const = 0;
	virtual std::shared_ptr<GameObject> MoveClone() = 0;

	virtual glm::vec2 GetLowestPoint() const = 0;
	virtual float GetHeight() const = 0;
	virtual float GetWidth() const = 0;

	const std::string& GetName() const;
	const std::vector<std::shared_ptr<Mesh>>& GetMeshes();
	Transform& GetTransform();
	Physics& GetPhysics();
	Collision& GetCollision();

	virtual void Update(float deltaTime) = 0;

	virtual void OnCollisionStart(const std::shared_ptr<GameObject>& other) { }

	virtual void ShowDebugControls(glm::vec2 pos) { }
};

