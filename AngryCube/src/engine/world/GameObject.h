#pragma once
#include <string>
#include <memory>
#include <unordered_set>

#include "engine/components/collision/Collision.h"
#include "engine/components/mesh/Mesh.h"
#include "engine/components/collision/CollisionMesh.h"
#include "engine/components/physics/Physics.h"
#include "engine/components/transform/Transform.h"

class Scene;


class GameObject
{
protected:
	std::string name;
	
	Scene* scene;
	GameObject* parent = nullptr;
	std::unordered_set<std::shared_ptr<GameObject>> children;

	// components
	std::vector<std::shared_ptr<Mesh>> meshes;
	Transform transform;
	Physics physics;
	Collision collision;
	std::shared_ptr<CollisionMesh> collisionMesh = nullptr;

public:
	GameObject(Scene* parentScene, float mass = 1.0f, const std::shared_ptr<CollisionMesh>& collisionMesh = nullptr);
	virtual ~GameObject() = default;

	GameObject(const GameObject& other);
	GameObject& operator= (const GameObject& other);

	GameObject(GameObject&& other) noexcept;
	GameObject& operator= (GameObject&& other) noexcept;

	virtual std::shared_ptr<GameObject> Clone() const = 0;
	virtual std::shared_ptr<GameObject> MoveClone() = 0;

	GameObject* GetParent() const;
	const std::unordered_set<std::shared_ptr<GameObject>>& GetChildren() const;
	bool HasChild(const std::shared_ptr<GameObject>& child) const;

	virtual void AttachChild(const std::shared_ptr<GameObject>& child, bool disablePhysics = true);
	virtual void RemoveChild(const std::shared_ptr<GameObject>& child);

	const std::string& GetName() const;
	
	const std::vector<std::shared_ptr<Mesh>>& GetMeshes();
	
	std::shared_ptr<CollisionMesh> GetCollisionMesh();
	std::shared_ptr<const CollisionMesh> GetCollisionMesh() const;
	
	Transform& GetTransform();
	const Transform& GetTransform() const;
	
	Physics& GetPhysics();
	const Physics& GetPhysics() const;
	
	Collision& GetCollision();
	const Collision& GetCollision() const;

	virtual void Update(float deltaTime) = 0;

	virtual void OnCollisionStart(const std::shared_ptr<GameObject>& other) {};

	virtual void ShowDebugControls();
};
