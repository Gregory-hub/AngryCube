#pragma once
#include "engine/world/GameObject.h"


class Catapult : public GameObject
{
private:
    static int id;

public:
	Catapult();
	~Catapult() override = default;

	Catapult(const Catapult& other) = default;
	Catapult& operator= (const Catapult& other) = default;

	Catapult(Catapult&& other) noexcept = default;
	Catapult& operator= (Catapult&& other) noexcept = default;

	std::shared_ptr<GameObject> Clone() const override;
	std::shared_ptr<GameObject> MoveClone() override;

	void Update(float deltaTime) override;

	void ShowDebugControls(glm::vec2 pos) override;
};

