#include "DefaultMeshes.h"


CubeMesh::CubeMesh()
{
    triangles = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };
    SetSizes(width, height);
}

void CubeMesh::SetSizes(int w, int h)
{
    width = w;
    height = h;

    float x0 = -width / 2.0f;
    float x1 = width / 2.0f;
    float y0 = -height / 2.0f;
    float y1 = height / 2.0f;

    vertices = {
        { x0, y0 },
        { x1, y0 },
        { x1, y1 },
        { x0, y1 }
    };

	UpdateBuffers();
}

