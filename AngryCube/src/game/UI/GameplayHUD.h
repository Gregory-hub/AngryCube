#pragma once
#include "engine/UI/Button.h"
#include "engine/UI/HUD.h"
#include "engine/UI/Slider.h"
#include "game/CatapultController.h"

class GameplayHUD : public HUD
{
private:
    std::shared_ptr<CatapultController> controller;
    std::unique_ptr<Button> releaseOrCockButton;
    std::unique_ptr<Slider<float>> tensionSlider;
    std::unique_ptr<Slider<float>> angleSlider;
 
public:
    GameplayHUD(std::shared_ptr<CatapultController> catapultController);
    void Render() const override;

private:
    void OnButtonReleaseCockPressed() const;
    
    float GetTension() const;
    void SetTension(float newTension) const;
    
    float GetAngle() const;
    void SetAngle(float newAngle) const;
};
