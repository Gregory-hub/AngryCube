#pragma once
#include "engine/components/mesh/Mesh.h"


class CollisionMesh : public GameObjectComponent
{
private:
	std::shared_ptr<Mesh> baseMesh;
	glm::vec2 lowestPoint;
	float width;
	float height;

public:
	CollisionMesh(GameObject* parentObject, const std::shared_ptr<Mesh>& mesh);
	~CollisionMesh() override = default;

	CollisionMesh(const CollisionMesh& other) = default;
	CollisionMesh& operator= (const CollisionMesh& other) = default;

	CollisionMesh(CollisionMesh&& other) noexcept = default;
	CollisionMesh& operator= (CollisionMesh&& other) noexcept = default;

	std::shared_ptr<Mesh> GetBaseMesh();

	glm::vec2 GetLowestPoint() const;
	float GetHeight() const;
	float GetWidth() const;
};

