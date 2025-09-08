#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"


class Cube : public Model
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

    void Update(float deltaTime) override;

    void ShowDebugControls(glm::vec2 pos) override;
};

