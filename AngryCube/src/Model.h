#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Model
{
protected:
    std::string name;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    glm::vec3 translation { 0.0f, 0.0f, -1.0f };
    float rotation = 0.0f;      // degrees
    glm::vec3 scale { 1.0f, 1.0f, 1.0f };

public:
    virtual ~Model() = default;

    virtual void Bind() const;
    virtual void Unbind() const;

    virtual glm::vec3 GetTranslation() const;
    virtual float GetRotation() const;
    virtual glm::vec3 GetScale() const;

    virtual void SetTranslation(const glm::vec3& value);
    virtual void SetRotation(const float value);
    virtual void SetScale(const glm::vec3& value);

    virtual void Move(const glm::vec3& value);
    virtual void Rotate(const float value);
    virtual void Scale(const glm::vec3& value);

    virtual void Update(float deltaTime) {};

    virtual glm::mat4 GetTransformMatrix() const;
    virtual unsigned int GetIndexCount() const = 0;

    virtual void ShowDebugControls(glm::vec2 pos) {};
};

