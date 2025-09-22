#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "engine/world/GameObject.h"


class Cube : public GameObject
{
private:
    static int id;

    float mass;
    glm::vec2 pushDirection = { 0.0f, 0.0f };

public:
    Cube();
    Cube(float mass);
    ~Cube() override = default;

    Cube(const Cube& other);
    Cube& operator= (const Cube& other);

    Cube(Cube&& other) noexcept;
    Cube& operator= (Cube&& other) noexcept;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

	glm::vec2 GetLowestPoint() const override;
	float GetHeight() const override;
	float GetWidth() const override;

    void Update(float deltaTime) override;

	void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;

    void ShowDebugControls(glm::vec2 pos) override;
};

