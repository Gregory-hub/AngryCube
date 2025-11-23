#pragma once
#include "engine/UI/Slider.h"
#include "engine/UI/Widget.h"


class CatapultControlsWidget : public Widget
{
private:
    std::unique_ptr<Slider<float>> tensionSlider;
    std::unique_ptr<Slider<float>> angleSlider;

    float positionX = 300.0f;

public:
    CatapultControlsWidget();

    void Render() const override;
    void Reset() override;

    void SetPositionX(float newX);

private:
    void OnButtonReleaseCockPressed() const;

    float GetTension() const;
    void SetTension(float newTension) const;

    float GetAngle() const;
    void SetAngle(float newAngle) const;
};
