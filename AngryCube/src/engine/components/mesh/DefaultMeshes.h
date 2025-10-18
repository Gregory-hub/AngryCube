#pragma once

#include "Mesh.h"


class CubeMesh : public Mesh
{
private:
	float width;
	float height;

public:
	CubeMesh(float w = 100.0f, float h = 100.0f);

	float GetWidth() const;
	float GetHeight() const;
	void SetSizes(float w, float h);
};
