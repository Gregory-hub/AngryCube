#pragma once
#include "Settings.h"
#include "engine/UI/Button.h"
#include "engine/UI/HUD.h"
#include "engine/UI/Slider.h"
#include "game/CatapultController.h"


class GameplayHUD : public HUD
{
private:
    std::unique_ptr<Button> releaseOrCockButton;
    std::unique_ptr<Slider<float>> tensionSlider;
    std::unique_ptr<Slider<float>> angleSlider;

    glm::ivec2 controlsPosition;
    glm::ivec2 controlsPositionShift = { 70, -40 };
 
public:
    GameplayHUD();

    void Reset() override;
    void Render() const override;

private:
    void OnButtonReleaseCockPressed() const;
    
    float GetTension() const;
    void SetTension(float newTension) const;
    
    float GetAngle() const;
    void SetAngle(float newAngle) const;
};
