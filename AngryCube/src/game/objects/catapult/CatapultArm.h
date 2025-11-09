#pragma once
#include "engine/world/GameObject.h"
#include "game/interfaces/IProjectile.h"


class Cube;

enum class CatapultArmMode : uint8_t
{
    Free,
    Cocked,
    Released,
    Cocking,
    Loading
};


class CatapultArm : public GameObject
{
private:
    static int id;

    std::shared_ptr<Cube> arm;
    std::shared_ptr<Cube> projectileSocket;
    std::shared_ptr<GameObject> projectile = nullptr;

    CatapultArmMode armMode = CatapultArmMode::Free;

    glm::vec2 socketDisplacement = glm::vec2(0.0f, -2.0f);

    float minAngle = 15.0f;
    float maxAngle = 60.0f;
    float progress = 0.0f;  // 0 to 1

    float targetMaxAngle = maxAngle;

    float pullbackSpeed = 1.0f;

    float armMass = 50.0f;
    float socketMass = 5.0f;
    float k = 5000.0;

    float timeFromRelease = 0.0f;

    float projectileMass = 50.0f;

public:
    CatapultArm(Scene* parentScene);

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    float GetProgress() const;
    void SetProgress(float newProgress);
    void AddProgress(float newProgress);

    CatapultArmMode GetArmMode() const;

    float GetMinAngle() const;
    
    float GetMaxAngle() const;
    void SetMaxAngle(float newMaxAngle);

    float GetArmLength() const;
    void SetArmScale(const glm::vec2& scale);

    float GetArmMass() const;
    void SetArmMass(float newArmMass);

    float GetSocketMass() const;
    void SetSocketMass(float newSocketMass);

    float GetK() const;
    void SetK(float k);

    void Update(float deltaTime) override;
    void UpdateArmProgress(float deltaTime);

    void Release();
    void Cock();

    std::shared_ptr<GameObject> GetProjectile() const;
    void LoadProjectile(const std::shared_ptr<IProjectile>& newProjectile);
    void DetachProjectile(bool shoot = true);

    void ShowDebugControls() override;

private:
    void MoveArmIntoPlace();
    void MoveSocketIntoPlace();
    
    float CalculateArmProgress(float t);
    glm::vec2 CalculateProjectileVelocity() const;

    void UpdateArmMode();
};
