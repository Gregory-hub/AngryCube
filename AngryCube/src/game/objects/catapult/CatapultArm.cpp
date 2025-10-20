#include "pch.h"
#include "CatapultArm.h"

#include "game/objects/Cube.h"
#include "imgui.h"
#include "engine/components/physics/constants.h"
#include <game/objects/projectiles/ProjectileCube.h>


int CatapultArm::id = 0;


CatapultArm::CatapultArm(Scene* parentScene)
    :   GameObject(parentScene, 0.0f),
        arm(std::make_shared<Cube>(parentScene, armMass)),
        projectileSocket(std::make_shared<Cube>(parentScene, socketMass))
{
    name = "CatapultArm " + std::to_string(id);

    AttachChild(arm);
    arm->AttachChild(projectileSocket);
    projectileSocket->GetTransform().SetScale(glm::vec2(
            arm->GetTransform().GetScale().x / 3.0f,
            arm->GetTransform().GetScale().y / 6.0f));

    MoveArmIntoPlace();

    SetProgress(0.0f);
}

std::shared_ptr<GameObject> CatapultArm::Clone() const
{
    return std::make_shared<CatapultArm>(*this);
}

std::shared_ptr<GameObject> CatapultArm::MoveClone()
{
    return std::make_shared<CatapultArm>(std::move(*this));
}

void CatapultArm::SetProgress(float newProgress)
{
    if (newProgress < 0.0f)
        newProgress = 0.0f;
    else if (newProgress > 1.0f)
        newProgress = 1.0f;
    progress = newProgress;

    float angle = minAngle + newProgress * (maxAngle - minAngle);
    GetTransform().SetRotation(-angle);
}

float CatapultArm::GetProgress() const
{
    return progress;
}

void CatapultArm::AddProgress(float newProgress)
{
    SetProgress(progress + newProgress);
}

float CatapultArm::GetMinAngle() const
{
    return minAngle;
}

float CatapultArm::GetMaxAngle() const
{
    return maxAngle;
}

float CatapultArm::GetArmLength() const
{
    return arm->GetCollisionMesh()->GetWidth();
}

void CatapultArm::SetArmScale(const glm::vec2& scale)
{
    arm->GetTransform().SetScale(scale);
    arm->GetTransform().SetTranslation(-glm::vec2(arm->GetTransform().GetScale().x / 2.0f * 100.0f, 0.0f));
}

float CatapultArm::GetArmMass() const
{
    return armMass;
}

void CatapultArm::SetArmMass(float newArmMass)
{
    armMass = newArmMass;
    arm->GetPhysics().SetMass(newArmMass);
}

float CatapultArm::GetSocketMass() const
{
    return socketMass;
}

void CatapultArm::SetSocketMass(float newSocketMass)
{
    socketMass = newSocketMass;
    projectileSocket->GetPhysics().SetMass(newSocketMass);
}

float CatapultArm::GetK() const
{
    return k;
}

void CatapultArm::SetK(float k)
{
    this->k = k;
}

void CatapultArm::Update(float deltaTime)
{
    UpdateArmProgress(deltaTime);
    UpdateArmMode();
}

void CatapultArm::UpdateArmProgress(float deltaTime)
{
    if (armMode == CatapultArmMode::Released)
    {
        timeFromRelease += deltaTime;
        float newProgress = CalculateArmProgress(timeFromRelease);

        SetProgress(newProgress);
        if (progress >= 1.0f)
            DetachProjectile();
    }
    else if (armMode == CatapultArmMode::Cocking)
    {
        AddProgress(-pullbackSpeed * deltaTime);
        if (progress <= 0.0f && !projectile)
        {
            std::shared_ptr<ProjectileCube> newProjectile = std::make_shared<ProjectileCube>(scene, projectileMass);
            newProjectile->GetTransform().SetScale(glm::vec2(0.2f, 0.2f));
            LoadProjectile(newProjectile);
        }
    }
}

void CatapultArm::Release()
{
    if (armMode == CatapultArmMode::Cocked)
    {
        armMode = CatapultArmMode::Released;
        timeFromRelease = 0.0f;
    }
}

void CatapultArm::Cock()
{
    if (armMode != CatapultArmMode::Released)
        armMode = CatapultArmMode::Cocking;
}

void CatapultArm::LoadProjectile(const std::shared_ptr<GameObject>& newProjectile)
{
    if (projectile)
        DetachProjectile(false);

    projectile = newProjectile;
    projectileSocket->AttachChild(projectile);
    projectile->GetTransform().SetTranslation(glm::vec2(0.0f, 5.0f));
}

void CatapultArm::DetachProjectile(bool shoot)
{
    if (projectile)
    {
        if (shoot)
        {
            projectile->GetPhysics().Enable();
            projectile->GetPhysics().SetVelocity(CalculateProjectileVelocity());
        }
        projectileSocket->RemoveChild(projectile);
        projectile->GetTransform().Move(projectileSocket->GetTransform().GetWorldTranslation());
        projectile = nullptr;
    }
}

void CatapultArm::ShowDebugControls()
{
    GameObject::ShowDebugControls();
    ImGui::DragFloat("Projectile mass", &projectileMass, 0.1f, 0.0f, 1000.0f);
}

void CatapultArm::MoveArmIntoPlace()
{
    if (arm)
    {
        arm->GetTransform().SetTranslation(glm::vec2(-arm->GetTransform().GetScale().x / 2.0f * 100.0f, 0.0f));
        MoveSocketIntoPlace();
    }
}

void CatapultArm::MoveSocketIntoPlace()
{
    if (projectileSocket)
    {
        projectileSocket->GetTransform().SetTranslation(glm::vec2(-0.5 * GetArmLength(), 0.0f) + socketDisplacement);
    }
}

float CatapultArm::CalculateArmProgress(float t)
{
    float phase = 180;
    float x = GetArmLength() / CM_IN_METER;
    float M = armMass + socketMass;
    float m = projectile->GetPhysics().GetMass();

    float underSq = k / (M / 3 + m);
    return 1.0f + glm::cos(1 / x * glm::sqrt(underSq) * t + glm::radians(phase));
}

glm::vec2 CatapultArm::CalculateProjectileVelocity() const
{
    float amplitude = 0.0f;
    glm::vec2 normal;
    if (projectile)
    {
        float x = GetArmLength() / CM_IN_METER;
        float M = armMass + socketMass;
        float m = projectile->GetPhysics().GetMass();
        amplitude = 0.5f * x * glm::sqrt(3.0f * k / (m + M / 3.0f));

        glm::vec2 socketTranslation = projectileSocket->GetTransform().GetWorldTranslation() - socketDisplacement;
        glm::vec2 armTranslation = GetTransform().GetWorldTranslation();
        glm::vec2 d = socketTranslation - armTranslation;
        normal = glm::normalize(glm::vec2(d.y, -d.x));
    }
    return amplitude * normal;
}

void CatapultArm::UpdateArmMode()
{
    if (progress <= 0.0f)
        armMode = CatapultArmMode::Cocked;
    else if (progress >= 1.0f)
        armMode = CatapultArmMode::Free;
    else if (progress > 0.0f && armMode == CatapultArmMode::Cocked)
        armMode = CatapultArmMode::Free;
}
