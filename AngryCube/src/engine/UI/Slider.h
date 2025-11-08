#pragma once
#include "Widget.h"
#include "engine/utility/ImGuiDragFloatWithSetter.h"

template<typename T>
class Slider : public Widget
{
private:
    std::string text;
    std::function<T()> getter;
    std::function<void(T)> setter;

public:
    // template<typename T>
    Slider(std::string sliderText, std::function<T()> valueGetter, std::function<void(T)> valueSetter)
        : text(std::move(sliderText)), getter(std::move(valueGetter)), setter(std::move(valueSetter))
    {
    }

    // template<typename T>
    void Render() const override
    {
        ImGui::DragFloatWithSetter(text.c_str(), getter, setter, 1.0f, 0.0f, 10000.0f);
    }
};
