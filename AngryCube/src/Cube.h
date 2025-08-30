#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Cube
{
private:
    glm::vec2 vertices[4] = {
        { -0.5f, -0.5f },
        { 0.5f, -0.5f },
        { 0.5f, 0.5f },
        { -0.5f, 0.5f }
    };

    glm::uvec3 indices[2] = {
        { 0, 1, 3 },
        { 1, 2, 3 }
    };

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

public:
    Cube();
    ~Cube();

    void Bind();
    void Unbind();

    unsigned int GetIndexCount() const;
};

