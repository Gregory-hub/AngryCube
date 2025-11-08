#include "pch.h"
#include "Button.h"


Button::Button(std::string textInside, std::function<void()> onPressedCallback)
    : text(std::move(textInside)), onPressed(std::move(onPressedCallback))
{
}

void Button::Render() const
{
    if (ImGui::Button(text.c_str()))
        onPressed();
}
