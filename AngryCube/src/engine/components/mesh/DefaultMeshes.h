#pragma once

#include "Mesh.h"


class CubeMesh : public Mesh
{
private:
	float width = 100;
	float height = 100;
public:
	CubeMesh();

	float GetWidth() const;
	float GetHeight() const;
	void SetSizes(float w, float h);
};

