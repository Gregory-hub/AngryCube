#pragma once

#include <memory>

#include "engine/world/GameObject.h"


class Cube : public GameObject
{
private:
    static int id;

public:
    Cube(Scene* parentScene, float mass = 1.0f);
    ~Cube() override = default;

    Cube(const Cube& other);
    Cube& operator= (const Cube& other);

    Cube(Cube&& other) noexcept = default;
    Cube& operator= (Cube&& other) noexcept = default;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    void Update(float deltaTime) override;

	void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;
};
