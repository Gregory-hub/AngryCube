#include "pch.h"
#include "GameplayHUD.h"

#include <utility>

#include "engine/utility/Logger.h"

GameplayHUD::GameplayHUD(std::shared_ptr<CatapultController> catapultController)
    : releaseOrCockButton(std::make_unique<Button>("Release|Cock", [this] { OnButtonReleaseCockPressed(); })),
    controller(std::move(catapultController))
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
    controller->ReleaseOrCock();
    Logger::Log(LogLevel::Info, "ReleaseCock pressed");
}
