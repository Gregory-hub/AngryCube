#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/Mesh.h"
#include "engine/Transform.h"


class Cube : public Mesh
{
private:
    static int id;

    float x = 0.0f;
    float speed = 1.0f;

    glm::vec3 startingTranslation;
    glm::vec3 startingScale;
    bool startedMovement = false;

public:
    Cube();
    ~Cube() = default;

    Cube(const Cube& other);
    Cube& operator= (const Cube& other);

    Cube(Cube&& other) noexcept;
    Cube& operator= (Cube&& other) noexcept;

    void Update(float deltaTime) override;

    void ShowDebugControls(glm::vec2 pos) override;
};

