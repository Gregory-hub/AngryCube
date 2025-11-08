#pragma once
#include "engine/UI/Button.h"
#include "engine/UI/HUD.h"

class GameplayHUD : public HUD
{
private:
    std::unique_ptr<Button> releaseOrCockButton;
 
public:
    GameplayHUD();
    void Render() const override;

private:
    void OnButtonReleaseCockPressed();
};
