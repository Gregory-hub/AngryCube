#include "CollisionMesh.h"

#include "stdexcept"


CollisionMesh::CollisionMesh(const std::shared_ptr<Mesh>& mesh)
	: GameObjectComponent(nullptr), baseMesh(mesh)
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

std::shared_ptr<Mesh> CollisionMesh::GetBaseMesh()
{
	return baseMesh;
}

glm::vec2 CollisionMesh::GetLowestPoint() const
{
	return lowestPoint;
}

float CollisionMesh::GetHeight() const
{
	return height;
}

float CollisionMesh::GetWidth() const
{
	return width;
}
