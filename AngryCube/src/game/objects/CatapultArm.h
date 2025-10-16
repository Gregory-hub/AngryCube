#pragma once
#include "engine/world/GameObject.h"


enum class CatapultArmMode : uint8_t
{
    Free,
    Pullback,
    Release
};


class CatapultArm : public GameObject
{
private:
    static int id;

    std::shared_ptr<GameObject> arm;
    CatapultArmMode armMode = CatapultArmMode::Free;

    float minAngle = 15.0f;
    float maxAngle = 80.0f;
    float progress = 0.0f;  // 0 to 1

    float releaseSpeed = 8.0f;
    float pullbackSpeed = 0.5f;

public:
    CatapultArm();

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;

    float GetProgress() const;
    void SetProgress(float progress);
    void AddProgress(float progress);

    float GetMinAngle() const;
    float GetMaxAngle() const;

    void SetArmScale(glm::vec2 scale);

    void Update(float deltaTime) override;
    void UpdateArmProgress(float deltaTime);

    void Release();
    void Pullback();

    void ShowDebugControls() override;
};
