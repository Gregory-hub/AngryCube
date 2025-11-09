#include "pch.h"
#include "GameplayHUD.h"

#include <utility>

#include "engine/UI/Slider.h"


GameplayHUD::GameplayHUD(std::shared_ptr<CatapultController> catapultController)
    : controller(std::move(catapultController)),
    releaseOrCockButton(std::make_unique<Button>("Release|Cock", [this] { OnButtonReleaseCockPressed(); })),
    tensionSlider(std::make_unique<Slider<float>>("Tension",
        [this] { return GetTension(); },
        [this] (float value) { SetTension(value); },
        3.0f, 1000.0f, 10000.0f)),
    angleSlider(std::make_unique<Slider<float>>("Angle",
        [this] { return GetAngle(); },
        [this] (float value) { SetAngle(value); },
        0.05f))
{
    if (controller)
    {
        angleSlider->SetMinValue(controller->GetMaxAngleLowerBound());
        angleSlider->SetMaxValue(controller->GetMaxAngleUpperBound());
    }

    position = glm::ivec2(0, Settings::GetWindowResolution().y / 2);
}

void GameplayHUD::Render() const
{
    ImGui::SetNextWindowPos(ImVec2(position.x + shift.x, position.y + shift.y), ImGuiCond_Once);
    ImGui::Begin("Catapult", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    tensionSlider->Render();
    angleSlider->Render();
    releaseOrCockButton->Render();
    ImGui::End();
}

void GameplayHUD::OnButtonReleaseCockPressed() const
{
    if (controller)
        controller->ReleaseOrCock();
}

float GameplayHUD::GetTension() const
{
    if (controller)
        return controller->GetTension();
    return 0.0f;
}

void GameplayHUD::SetTension(float newTension) const
{
    if (controller)
        controller->SetTension(newTension);
}

float GameplayHUD::GetAngle() const
{
    if (controller)
        return controller->GetAngle();
    return 0.0f;
}

void GameplayHUD::SetAngle(float newAngle) const
{
    if (controller)
        controller->SetAngle(newAngle);
}
