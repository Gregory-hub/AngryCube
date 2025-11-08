#include "pch.h"
#include "GameplayHUD.h"

#include "engine/utility/Logger.h"

GameplayHUD::GameplayHUD()
    : releaseOrCockButton(std::make_unique<Button>("Release|Cock",
        [this] { OnButtonReleaseCockPressed(); }))
{
}

void GameplayHUD::Render() const
{
    ImGui::Begin("HUD");
    releaseOrCockButton->Render();
    ImGui::End();
}

void GameplayHUD::OnButtonReleaseCockPressed()
{
    Logger::Log(LogLevel::Info, "ReleaseCock pressed");
}
