#pragma once
#include "game/objects/Cube.h"


class FlatGround : public Cube
{
private:
	static unsigned int id;
	float height;

public:
	FlatGround(Scene* parentScene, float height);

	float GetHeight() const;
	void SetHeight(float newHeight);
};
