#pragma once
#include "engine/world/GameObject.h"

#include "CatapultArm.h"


class Catapult : public GameObject
{
private:
    static int id;

	std::shared_ptr<CatapultArm> arm;

public:
	Catapult(Scene* parentScene);
	~Catapult() override = default;

	Catapult(const Catapult& other) = default;
	Catapult& operator= (const Catapult& other) = default;

	Catapult(Catapult&& other) noexcept = default;
	Catapult& operator= (Catapult&& other) noexcept = default;

	std::shared_ptr<GameObject> Clone() const override;
	std::shared_ptr<GameObject> MoveClone() override;

	void Release();
	void Cock();

	void Update(float deltaTime) override;

	void ShowDebugControls() override;

private:
	void SetMaterial(const std::shared_ptr<Material>& material);
};
