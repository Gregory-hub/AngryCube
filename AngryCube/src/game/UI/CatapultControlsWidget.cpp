#include "pch.h"
#include "CatapultControlsWidget.h"

#include "engine/core/Game.h"
#include "game/CatapultController.h"


CatapultControlsWidget::CatapultControlsWidget()
    :
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
    std::string title = "Level " + Game::GameLevelManager->GetActiveLevel()->GetName();
    int ammo = 0;
    if (auto catapult = catapultPtr.lock())
        ammo = catapult->GetCurrentAmmo();

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(positionX, io.DisplaySize.y / 2), ImGuiCond_Once, ImVec2(0.5f, 0.5f));

    auto flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
    ImGui::Begin(title.c_str(), nullptr, flags);

    tensionSlider->Render();
    angleSlider->Render();
    if (ImGui::Button("Release|Cock"))
        OnButtonReleaseCockPressed();
    ImGui::SameLine();
    ImGui::Text("Ammo left: %d", ammo);

    ImGui::End();
}

void CatapultControlsWidget::Reset()
{
    Widget::Reset();
    if (auto controller = dynamic_cast<CatapultController*>(Game::GameController.get()))
    {
        angleSlider->SetMinValue(controller->GetMaxAngleLowerBound());
        angleSlider->SetMaxValue(controller->GetMaxAngleUpperBound());
        catapultPtr = controller->GetCatapult();
    }
}

void CatapultControlsWidget::SetPositionX(float newX)
{
    positionX = newX;
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
