#pragma once

#include "Mesh.h"


class CubeMesh : public Mesh
{
private:
	float width;
	float height;

public:
	CubeMesh(float w = 100.0f, float h = 100.0f);

	std::shared_ptr<GameObjectComponent> Clone() const override;
	std::shared_ptr<GameObjectComponent> MoveClone() override;

	float GetWidth() const;
	float GetHeight() const;
	void SetSizes(float w, float h);
};
