#pragma once
#include "engine/UI/Slider.h"
#include "engine/UI/Widget.h"
#include "engine/UI/Button.h"


class CatapultControlsWidget : public Widget
{
private:
    std::unique_ptr<Button> releaseOrCockButton;
    std::unique_ptr<Slider<float>> tensionSlider;
    std::unique_ptr<Slider<float>> angleSlider;

    glm::ivec2 controlsPosition;
    glm::ivec2 controlsPositionShift = { 70, -40 };

public:
    CatapultControlsWidget();

    void Render() const override;
    void Reset() override;

private:
    void OnButtonReleaseCockPressed() const;

    float GetTension() const;
    void SetTension(float newTension) const;

    float GetAngle() const;
    void SetAngle(float newAngle) const;
};
