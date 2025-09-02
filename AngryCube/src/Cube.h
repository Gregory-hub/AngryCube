#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Cube
{
private:
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

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    glm::vec3 translation { 0.0f, 0.0f, -1.0f };
    float rotation = 0.0f;  // degrees
    glm::vec3 scale { 1.0f, 1.0f, 1.0f };

public:
    Cube();
    ~Cube();

    void Bind() const;
    void Unbind() const;

    void Move(const glm::vec3& value);
    void Rotate(const float value);
    void Scale(const glm::vec3& value);

    unsigned int GetIndexCount() const;

    glm::mat4 GetTransformMatrix() const;

    void ShowDebugControls();
};

