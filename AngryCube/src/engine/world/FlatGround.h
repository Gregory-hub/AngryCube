#pragma once
#include "engine/world/GameObject.h"


class FlatGround : public GameObject
{
private:
	static unsigned int id;
	float height = 0.0f;

public:
	FlatGround(Scene* parentScene, float height);

    FlatGround(const FlatGround& other);
    FlatGround& operator= (const FlatGround& other);

    FlatGround(FlatGround&& other) noexcept = default;
    FlatGround& operator= (FlatGround&& other) noexcept = default;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

	float GetHeight() const;
	void SetHeight(float newHeight);

    // Inherited via GameObject
    void Update(float deltaTime) override;
};
