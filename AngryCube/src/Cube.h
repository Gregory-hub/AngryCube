#pragma once

#include <glm/glm.hpp>

#include "engine/GameObject.h"


class Cube : public GameObject
{
private:
    static int id;

public:
    Cube();
    ~Cube() override = default;

    Cube(const Cube& other);
    Cube& operator= (const Cube& other);

    Cube(Cube&& other) noexcept;
    Cube& operator= (Cube&& other) noexcept;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    void Update(float deltaTime) override;

    void ShowDebugControls(glm::vec2 pos) override;
};

