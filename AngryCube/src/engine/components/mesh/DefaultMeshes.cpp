#include "pch.h"
#include "DefaultMeshes.h"

#include "engine/core/ShaderManager.h"


CubeMesh::CubeMesh(float w, float h)
	: width(w), height(h)
{
    shader = ShaderManager::GetShaderFor<CubeMesh>();
    triangles = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };
    SetSizes(width, height);
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

