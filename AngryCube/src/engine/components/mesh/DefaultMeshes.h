#pragma once

#include "Mesh.h"


class CubeMesh : public Mesh
{
private:
	int width = 100;
	int height = 100;
public:
	CubeMesh();
	void SetSizes(int w, int h);
};

