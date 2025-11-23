#include "pch.h"
#include "LevelLoseWidget.h"
#include "Settings.h"
#include "engine/core/Game.h"

LevelLoseWidget::LevelLoseWidget()
    : position(Settings::GetWindowResolution() / 2)
{
}

bool LevelLoseWidget::IsActive() const
{
    return isActive;
}

void LevelLoseWidget::Activate()
{
    isActive = true;
}

void LevelLoseWidget::Deactivate()
{
    isActive = false;
}

void LevelLoseWidget::Render() const
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

void LevelLoseWidget::Reset()
{
    Widget::Reset();
    isActive = false;
}

void LevelLoseWidget::OnButtonQuitPressed() const
{
    Game::Quit();
}

void LevelLoseWidget::OnButtonRestartPressed() const
{
    Game::GameLevelManager->Load(Game::GameLevelManager->GetCurrentLevelIndex());
}
