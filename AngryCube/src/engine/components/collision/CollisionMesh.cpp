#include "pch.h"
#include "CollisionMesh.h"

#include "stdexcept"

#include "engine/world/GameObject.h"


CollisionMesh::CollisionMesh(GameObject* parent, const std::shared_ptr<Mesh>& mesh)
	: GameObjectComponent(parent), baseMesh(mesh)
{
	if (mesh->GetVertices().empty())
		throw std::invalid_argument("Mesh must contain vertices");

	float top = mesh->GetVertices()[0].y;
	float bottom = mesh->GetVertices()[0].y;
	float left = mesh->GetVertices()[0].x;
	float right = mesh->GetVertices()[0].x;

	for (const glm::vec2& vertex : mesh->GetVertices())
	{
		if (vertex.y <= bottom)
		{
			bottom = vertex.y;
			lowestPoint = vertex;
		}
		top = std::max(top, vertex.y);
		right = std::max(right, vertex.x);
		left = std::min(left, vertex.x);
	}
	width = right - left;
	height = top - bottom;
}

CollisionMesh::CollisionMesh(const CollisionMesh& other)
	: GameObjectComponent(other)
{
	baseMesh = std::dynamic_pointer_cast<Mesh>(other.baseMesh->Clone());
	lowestPoint = other.lowestPoint;
	width = other.width;
	height = other.height;
}

CollisionMesh& CollisionMesh::operator=(const CollisionMesh& other)
{
	if (this != &other)
	{
		baseMesh = std::dynamic_pointer_cast<Mesh>(other.baseMesh->Clone());
		lowestPoint = other.lowestPoint;
		width = other.width;
		height = other.height;
	}
	return *this;
}

std::shared_ptr<GameObjectComponent> CollisionMesh::Clone() const
{
	return std::make_shared<CollisionMesh>(*this);
}

std::shared_ptr<GameObjectComponent> CollisionMesh::MoveClone()
{
	return std::make_shared<CollisionMesh>(std::move(*this));
}

std::shared_ptr<Mesh> CollisionMesh::GetBaseMesh()
{
	return baseMesh;
}

glm::vec2 CollisionMesh::GetLowestPoint() const
{
	float yScale = parentObject->GetTransform().GetScale().y;
	return parentObject->GetTransform().GetWorldTranslation() - height * yScale / 2.0f;
}

float CollisionMesh::GetHeight() const
{
	return parentObject->GetTransform().GetScale().y * height;
}

float CollisionMesh::GetWidth() const
{
	return parentObject->GetTransform().GetScale().x * width;
}
