#pragma once
#include "Widget.h"


class Button : public Widget
{
private:
    std::string text;
    std::function<void()> onPressed;

public:
    Button(std::string textInside, std::function<void()> onPressedCallback);

    void Render() const override;
};
