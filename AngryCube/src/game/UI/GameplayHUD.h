#pragma once
#include "engine/UI/Button.h"
#include "engine/UI/HUD.h"
#include "game/CatapultController.h"

class GameplayHUD : public HUD
{
private:
    std::unique_ptr<Button> releaseOrCockButton;
    std::shared_ptr<CatapultController> controller;
 
public:
    GameplayHUD(std::shared_ptr<CatapultController> catapultController);
    void Render() const override;

private:
    void OnButtonReleaseCockPressed();
};
