#pragma once
#include "CatapultControlsWidget.h"
#include "engine/UI/HUD.h"


class GameplayHUD : public HUD
{
private:
    std::unique_ptr<CatapultControlsWidget> catapultControls;
 
public:
    GameplayHUD();

    void Reset() override;
    void Render() const override;
};
