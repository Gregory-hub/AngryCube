#include "DefaultMeshes.h"


CubeMesh::CubeMesh()
{
    vertices = {
        { -50.0f, -50.0f },
        { 50.0f, -50.0f },
        { 50.0f, 50.0f },
        { -50.0, 50.0f }
    };

    triangles = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };
	UpdateBuffers();
}

