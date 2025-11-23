#include "pch.h"
#include "CatapultControlsWidget.h"

#include "Settings.h"
#include "engine/core/Game.h"
#include "game/CatapultController.h"


CatapultControlsWidget::CatapultControlsWidget()
    : releaseOrCockButton(std::make_unique<Button>("Release|Cock",
        [this] { OnButtonReleaseCockPressed(); })),
    tensionSlider(std::make_unique<Slider<float>>("Tension",
        [this] { return GetTension(); },
        [this] (float value) { SetTension(value); },
        3.0f, 1000.0f, 10000.0f)),
    angleSlider(std::make_unique<Slider<float>>("Angle",
        [this] { return GetAngle(); },
        [this] (float value) { SetAngle(value); },
        0.05f))
{
    Reset();
}

void CatapultControlsWidget::Render() const
{
    ImGui::SetNextWindowPos(ImVec2(controlsPosition.x + controlsPositionShift.x, controlsPosition.y + controlsPositionShift.y), ImGuiCond_Once);
    ImGui::Begin("Catapult", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    tensionSlider->Render();
    angleSlider->Render();
    releaseOrCockButton->Render();
    ImGui::End();
}

void CatapultControlsWidget::Reset()
{
    Widget::Reset();
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
    {
        angleSlider->SetMinValue(controller->GetMaxAngleLowerBound());
        angleSlider->SetMaxValue(controller->GetMaxAngleUpperBound());
    }

    controlsPosition = glm::ivec2(0, Settings::GetWindowResolution().y / 2);
}

void CatapultControlsWidget::OnButtonReleaseCockPressed() const
{
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
        controller->ReleaseOrCock();
}

float CatapultControlsWidget::GetTension() const
{
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
        return controller->GetTension();
    return 0.0f;
}

void CatapultControlsWidget::SetTension(float newTension) const
{
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
        controller->SetTension(newTension);
}

float CatapultControlsWidget::GetAngle() const
{
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
        return controller->GetAngle();
    return 0.0f;
}

void CatapultControlsWidget::SetAngle(float newAngle) const
{
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
        controller->SetAngle(newAngle);
}
