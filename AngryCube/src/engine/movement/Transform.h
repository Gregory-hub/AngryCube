#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transform
{
private:
    glm::vec2 translation { 0.0f, 0.0f };
    float rotation = 0.0f;  // degrees
    glm::vec2 scale { 1.0f, 1.0f };

public:
    Transform() = default;
    ~Transform() = default;

    Transform(const Transform& other) = default;
    Transform& operator= (const Transform& other) = default;

    Transform(Transform&& other) noexcept;
    Transform& operator= (Transform&& other) noexcept;

    glm::vec2 GetTranslation() const;
    float GetRotation() const;
    glm::vec2 GetScale() const;

    void SetTranslation(const glm::vec2& value);
    void SetRotation(const float value);
    void SetScale(const glm::vec2& value);

    glm::mat4 GetMatrix() const;

    bool operator== (const Transform& other);
    bool operator== (const Transform& other) const;

    void ShowDebugControls();
};

