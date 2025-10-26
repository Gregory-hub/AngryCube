#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/components/GameObjectComponent.h"

class GameObject;


class Transform : public GameObjectComponent
{
private:
    bool enabled = true;

    glm::vec2 translation { 0.0f, 0.0f };
    float rotation = 0.0f;  // degrees
    glm::vec2 scale { 1.0f, 1.0f };

public:
    Transform(GameObject* parent);
    ~Transform() override = default;

    Transform(const Transform& other) = default;
    Transform& operator= (const Transform& other) = default;

    Transform(Transform&& other) noexcept = default;
    Transform& operator= (Transform&& other) noexcept = default;

    std::shared_ptr<GameObjectComponent> Clone() const override;
    std::shared_ptr<GameObjectComponent> MoveClone() override;

	void Enable();
	void Disable();
	bool Enabled() const;

    glm::vec2 GetTranslation() const;
    float GetRotation() const;
    glm::vec2 GetScale() const;

    glm::vec2 GetWorldTranslation() const;
    float GetWorldRotation() const;

    void SetTranslation(const glm::vec2& value);
    void SetRotation(float value);
    void SetScale(const glm::vec2& value);
    
    void SetWorldTranslation(const glm::vec2& value);
    void SetWorldRotation(float value);

	void Move(const glm::vec2& value);
	void Rotate(float value);
	void Scale(const glm::vec2& value);

    glm::mat4 GetMatrix() const;

    bool operator== (const Transform& other);
    bool operator== (const Transform& other) const;

    void ShowDebugControls();
};

