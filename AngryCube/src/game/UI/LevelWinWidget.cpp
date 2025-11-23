#include "pch.h"
#include "LevelWinWidget.h"

#include "Settings.h"
#include "engine/core/Game.h"


LevelWinWidget::LevelWinWidget()
    : position(Settings::GetWindowResolution() / 2)
{
}

bool LevelWinWidget::IsActive() const
{
    return isActive;
}

void LevelWinWidget::Activate()
{
    isActive = true;
}

void LevelWinWidget::Deactivate()
{
    isActive = false;
}

void LevelWinWidget::Render() const
{
    if (isActive)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(
            ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2),
            ImGuiCond_Once,
            ImVec2(0.5f, 2.0f));

        auto flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("You win", nullptr, flags);

        if (ImGui::Button("Quit"))
            OnButtonQuitPressed();
        ImGui::SameLine();
        if (ImGui::Button("Restart"))
            OnButtonRestartPressed();
        ImGui::SameLine();
        if (ImGui::Button("Next"))
            OnButtonNextPressed();

        ImGui::End();
    }
}

void LevelWinWidget::Reset()
{
    Widget::Reset();
    isActive = false;
}

void LevelWinWidget::OnButtonQuitPressed() const
{
    Game::Quit();
}

void LevelWinWidget::OnButtonRestartPressed() const
{
    Game::GameLevelManager->Load(Game::GameLevelManager->GetCurrentLevelIndex());
}

void LevelWinWidget::OnButtonNextPressed() const
{
    Game::GameLevelManager->LoadNext();
}
