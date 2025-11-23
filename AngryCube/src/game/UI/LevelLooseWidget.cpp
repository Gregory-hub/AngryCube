#include "pch.h"
#include "LevelLooseWidget.h"
#include "Settings.h"
#include "engine/core/Game.h"

LevelLooseWidget::LevelLooseWidget()
    : position(Settings::GetWindowResolution() / 2)
{
}

bool LevelLooseWidget::IsActive() const
{
    return isActive;
}

void LevelLooseWidget::Activate()
{
    isActive = true;
}

void LevelLooseWidget::Deactivate()
{
    isActive = false;
}

void LevelLooseWidget::Render() const
{
    if (isActive)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2),
            ImGuiCond_Once,
            ImVec2(0.5f, 0.5f)
        );

        auto flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("You Lose", nullptr, flags);

        if (ImGui::Button("Quit"))
            OnButtonQuitPressed();
        ImGui::SameLine();
        if (ImGui::Button("Restart"))
            OnButtonRestartPressed();

        ImGui::End();
    }
}

void LevelLooseWidget::Reset()
{
    Widget::Reset();
    isActive = false;
}

void LevelLooseWidget::OnButtonQuitPressed() const
{
    Game::Quit();
}

void LevelLooseWidget::OnButtonRestartPressed() const
{
    Game::GameLevelManager->Load(Game::GameLevelManager->GetCurrentLevelIndex());
}
