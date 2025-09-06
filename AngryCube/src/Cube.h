#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"


class Cube : public Model
{
private:
    static int id;

public:
    Cube();

    std::vector<glm::vec4> GetVertices() const override;
    std::vector<glm::uvec3> GetTriangles() const override;

    void ShowDebugControls(glm::vec2 pos) override;
};

