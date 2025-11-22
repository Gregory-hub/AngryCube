#include "pch.h"
#include "DefaultMeshes.h"

#include "engine/core/ShaderPool.h"


CubeMesh::CubeMesh(float w, float h)
	: width(w), height(h)
{
    shader = ShaderPool::GetShaderFor<CubeMesh>();
    triangles = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };
    SetSizes(width, height);
}

std::shared_ptr<GameObjectComponent> CubeMesh::Clone() const
{
	return std::make_shared<CubeMesh>(*this);
}

std::shared_ptr<GameObjectComponent> CubeMesh::MoveClone()
{
	return std::make_shared<CubeMesh>(std::move(*this));
}

float CubeMesh::GetWidth() const
{
    return width;
}

float CubeMesh::GetHeight() const
{
    return height;
}

void CubeMesh::SetSizes(float w, float h)
{
    width = w;
    height = h;

    float x0 = -width / 2.0f;
    float x1 = width / 2.0f;
    float y0 = -height / 2.0f;
    float y1 = height / 2.0f;

    SetVertices({
        { x0, y0 },
        { x1, y0 },
        { x1, y1 },
        { x0, y1 }
    });

	UpdateBuffers();
}

