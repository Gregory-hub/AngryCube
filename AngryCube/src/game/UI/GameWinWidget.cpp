#include "pch.h"
#include "GameWinWidget.h"
#include "Settings.h"
#include "engine/core/Game.h"

GameWinWidget::GameWinWidget()
    : position(Settings::GetWindowResolution() / 2)
{
}

bool GameWinWidget::IsActive() const
{
    return isActive;
}

void GameWinWidget::Activate()
{
    isActive = true;
}

void GameWinWidget::Deactivate()
{
    isActive = false;
}

void GameWinWidget::Render() const
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
        ImGui::Begin("Game Completed!", nullptr, flags);

        if (ImGui::Button("Quit"))
            OnButtonQuitPressed();
        ImGui::SameLine();
        if (ImGui::Button("Play Again"))
            OnButtonRestartPressed();

        ImGui::End();
    }
}

void GameWinWidget::Reset()
{
    Widget::Reset();
    isActive = false;
}

void GameWinWidget::OnButtonQuitPressed() const
{
    Game::Quit();
}

void GameWinWidget::OnButtonRestartPressed() const
{
    Game::GameLevelManager->LoadFirstLevel();
}
