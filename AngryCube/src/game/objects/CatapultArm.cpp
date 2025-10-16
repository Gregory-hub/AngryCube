#include "CatapultArm.h"

#include "Cube.h"
#include "imgui.h"
#include "engine/utility/ImGuiDragFloatWithSetter.h"


int CatapultArm::id = 0;

CatapultArm::CatapultArm()
    : arm(std::make_shared<Cube>())
{
    name = "CatapultArm " + std::to_string(id);
    AttachChild(arm);
    arm->GetTransform().SetTranslation(glm::vec2(-arm->GetTransform().GetScale().x / 2.0f * 100.0f, 0.0f));

    SetProgress(0.0f);

    // Debug show pivot
    // meshes.push_back(std::make_shared<CubeMesh>());
    // GetTransform().SetScale(glm::vec2(0.1f, 0.1f));
}

std::shared_ptr<GameObject> CatapultArm::Clone() const
{
    return std::make_shared<CatapultArm>(*this);
}

std::shared_ptr<GameObject> CatapultArm::MoveClone()
{
    return std::make_shared<CatapultArm>(std::move(*this));
}

void CatapultArm::SetProgress(float progress)
{
    if (progress < 0.0f)
        progress = 0.0f;
    else if (progress > 1.0f)
        progress = 1.0f;
    this->progress = progress;
    
    float angle = minAngle + progress * (maxAngle - minAngle);
    GetTransform().SetRotation(-angle);
}

float CatapultArm::GetProgress() const
{
    return progress;
}

void CatapultArm::AddProgress(float progress)
{
    SetProgress(this->progress + progress);
}

float CatapultArm::GetMinAngle() const
{
    return minAngle;
}

float CatapultArm::GetMaxAngle() const
{
    return maxAngle;
}

void CatapultArm::SetArmScale(glm::vec2 scale)
{
    arm->GetTransform().SetScale(scale);
    arm->GetTransform().SetTranslation(-glm::vec2(arm->GetTransform().GetScale().x / 2.0f * 100.0f, 0.0f));
}

void CatapultArm::Update(float deltaTime)
{
    UpdateArmProgress(deltaTime);
}

void CatapultArm::UpdateArmProgress(float deltaTime)
{
    if (armMode == CatapultArmMode::Release)
    {
        AddProgress(releaseSpeed * deltaTime);
        if (progress >= 1.0f)
            armMode = CatapultArmMode::Free;
    }
    else if (armMode == CatapultArmMode::Pullback)
    {
        AddProgress(-pullbackSpeed * deltaTime);
        if (progress <= 0.0f)
            armMode = CatapultArmMode::Free;
    }
}

void CatapultArm::Release()
{
    if (armMode != CatapultArmMode::Pullback)
        armMode = CatapultArmMode::Release;
}

void CatapultArm::Pullback()
{
    if (armMode != CatapultArmMode::Release)
        armMode = CatapultArmMode::Pullback;
}

void CatapultArm::ShowDebugControls()
{
    GameObject::ShowDebugControls();
    ImGui::DragFloatWithSetter("Progress", this, &CatapultArm::GetProgress, &CatapultArm::SetProgress, 0.01f, 0.0f, 1.0f);
    if (ImGui::Button("Release"))
        Release();
    if (ImGui::Button("Pullback"))
        Pullback();
}
