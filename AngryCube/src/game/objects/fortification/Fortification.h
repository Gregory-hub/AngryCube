#pragma once

#include <queue>

#include "engine/world/GameObject.h"
#include <game/interfaces/IDestructable.h>
#include <game/interfaces/IDestructableContainer.h>

#include "engine/saving/ISerializable.h"


class Fortification : public GameObject, public IDestructableContainer, public ISerializable
{
private:
    static int id;
    
    bool physicsEnabled = true;

    int brickCount = 0;
    bool winGameEnabled = false;

protected:
    std::queue<std::shared_ptr<IDestructable>> destructionQueue;

public:
    Fortification(Scene* parentScene);
    ~Fortification() override = default;

    Fortification(const Fortification& other);
    Fortification& operator=(const Fortification& other);
    
    Fortification(Fortification&& other) noexcept;
    Fortification& operator=(Fortification&& other) noexcept;

    std::shared_ptr<GameObject> Clone() const override;
    std::shared_ptr<GameObject> MoveClone() override;
    
    void AttachChild(const std::shared_ptr<GameObject>& child, bool disablePhysics) override;
    void RemoveChild(const std::shared_ptr<GameObject>& child) override;
    
    void Update(float deltaTime) override;

    void AddToDestructionQueue(std::shared_ptr<IDestructable> destroyed) override;

    void OnCollisionStart(const std::shared_ptr<GameObject>& other) override;
    
    nlohmann::json Serialize() override;
    void Deserialize(const nlohmann::json& json) override;

    void ShowDebugControls() override;

    void ToggleBricksPhysics();

    int GetBrickCount() const;
    bool GetWinGameEnabled() const;
    void SetWinGameEnabled(bool newWinGameEnabled);

private:
    void DestroyObjectsInQueue() override;
};
