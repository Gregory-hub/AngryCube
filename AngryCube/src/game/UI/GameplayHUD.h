#pragma once
#include "CatapultControlsWidget.h"
#include "LevelWinWidget.h"
#include "engine/UI/HUD.h"


class GameplayHUD : public HUD
{
private:
    std::unique_ptr<CatapultControlsWidget> catapultControls;
    std::unique_ptr<LevelWinWidget> levelWinWidget;
 
public:
    GameplayHUD();

    void Reset() override;
    void Render() const override;

    void ShowLevelWinWidget();
    void ShowLevelLooseWidget();
    void ShowGameWinWidget();
};
