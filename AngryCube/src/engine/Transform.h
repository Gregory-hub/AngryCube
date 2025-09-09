#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mesh;


class Transform
{
private:
    glm::vec3 translation { 0.0f, 0.0f, -1.0f };
    float rotation = 0.0f;  // degrees
    glm::vec3 scale { 1.0f, 1.0f, 1.0f };

public:
    glm::vec3 GetTranslation() const;
    float GetRotation() const;
    glm::vec3 GetScale() const;

    void SetTranslation(const glm::vec3& value);
    void SetRotation(const float value);
    void SetScale(const glm::vec3& value);

    glm::mat4 GetMatrix() const;

    bool operator == (const Transform& other);
    bool operator == (const Transform& other) const;

    void ShowDebugControls();
};

