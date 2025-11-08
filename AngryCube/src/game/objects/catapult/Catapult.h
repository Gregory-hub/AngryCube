#pragma once
#include "engine/world/GameObject.h"

#include "CatapultArm.h"


class Catapult : public GameObject
{
private:
    static int id;

	std::shared_ptr<CatapultArm> arm;
	std::shared_ptr<IProjectile> projectileTemplate;

public:
	Catapult(Scene* parentScene);
	~Catapult() override = default;

	Catapult(const Catapult& other) = default;
	Catapult& operator= (const Catapult& other) = default;

	Catapult(Catapult&& other) noexcept = default;
	Catapult& operator= (Catapult&& other) noexcept = default;

	std::shared_ptr<GameObject> Clone() const override;
	std::shared_ptr<GameObject> MoveClone() override;

	std::shared_ptr<IProjectile> GetProjectileTemplate() const;
	void SetProjectileTemplate(std::shared_ptr<IProjectile> newTemplate);

	void Load(std::shared_ptr<IProjectile> projectile = nullptr);
	void Release();
	void Cock();

	bool ReadyToRelease() const;

	void Update(float deltaTime) override;

	void ShowDebugControls() override;

private:
	void SetMaterial(const std::shared_ptr<Material>& material);
};
