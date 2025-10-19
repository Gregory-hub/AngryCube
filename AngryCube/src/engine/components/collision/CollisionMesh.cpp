#include "CollisionMesh.h"

#include "stdexcept"
#include "engine/world/GameObject.h"


CollisionMesh::CollisionMesh(GameObject* parentObject, const std::shared_ptr<Mesh>& mesh)
	: GameObjectComponent(parentObject), baseMesh(mesh)
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
	glm::vec4 tmp = parentObject->GetTransform().GetMatrix() * glm::vec4(lowestPoint, 0.0f, 1.0f);
	return { tmp.x, tmp.y };
}

float CollisionMesh::GetHeight() const
{
	return parentObject->GetTransform().GetScale().y * height;
}

float CollisionMesh::GetWidth() const
{
	return parentObject->GetTransform().GetScale().x * width;
}
