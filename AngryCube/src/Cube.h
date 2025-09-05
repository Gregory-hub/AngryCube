#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"


class Cube : public Model
{
private:
    static int id;

    glm::vec2 vertices[4] = {
        { -50.0f, -50.0f },
        { 50.0f, -50.0f },
        { 50.0f, 50.0f },
        { -50.0, 50.0f }
    };

    glm::uvec3 indices[2] = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };

public:
    Cube();
    ~Cube() override;

    unsigned int GetIndexCount() const override;

    void ShowDebugControls(glm::vec2 pos) override;
};
