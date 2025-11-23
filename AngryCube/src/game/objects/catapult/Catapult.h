#pragma once
#include "engine/world/GameObject.h"

#include "CatapultArm.h"
#include "engine/saving/ISerializable.h"


class Catapult : public GameObject, public ISerializable
{
private:
    static int id;

	std::shared_ptr<CatapultArm> arm;
	std::shared_ptr<IProjectile> projectileTemplate;

	float maxAngleUpperBound = 80.0f;
	float maxAngleLowerBound = 30.0f;

	int maxAmmo = 1;
	int currentAmmo = 1;

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

	float GetSpringTension() const;
	void SetSpringTension(float newTension) const;

	float GetMaxAngle() const;
	void SetMaxAngle(float newAngle) const;
	float GetMaxAngleUpperBound() const;
	float GetMaxAngleLowerBound() const;

    bool Load(std::shared_ptr<IProjectile> projectile = nullptr);
	void Release();
	void Cock();
	bool ReadyToRelease() const;

	void Update(float deltaTime) override;

	void ShowDebugControls() override;

    nlohmann::json Serialize() override;
    void Deserialize(const nlohmann::json& json) override;

    int GetCurrentAmmo() const;
    int GetMaxAmmo() const;
    void SetMaxAmmo(int maxAmmo);

private:
	void SetMaterial(const std::shared_ptr<Material>& material);
};
