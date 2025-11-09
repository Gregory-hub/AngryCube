#pragma once
#include "Widget.h"
#include "engine/utility/ImGuiDragFloatWithSetter.h"

template<typename T>
class Slider : public Widget
{
public:
    float GetSpeed() const;
    void SetSpeed(float speed);
    const T& GetMinValue() const;
    void SetMinValue(const T& minValue);
    const T& GetMaxValue() const;
    void SetMaxValue(const T& maxValue);

private:
    std::string text;
    std::function<T()> getter;
    std::function<void(T)> setter;
    float speed;
    T minValue;
    T maxValue;

public:
    // template<typename T>
    Slider(std::string sliderText, std::function<T()> valueGetter, std::function<void(T)> valueSetter, float valueSpeed = 1.0f, T minVal = 0.0f, T maxVal = 1.0f)
        : text(std::move(sliderText)), getter(std::move(valueGetter)), setter(std::move(valueSetter)), speed(valueSpeed), minValue(minVal), maxValue(maxVal)
    {
    }
    
    void Render() const override;
};

template <typename T>
float Slider<T>::GetSpeed() const
{
    return speed;
}

template <typename T>
void Slider<T>::SetSpeed(float speed)
{
    this->speed = speed;
}

template <typename T>
const T& Slider<T>::GetMinValue() const
{
    return minValue;
}

template <typename T>
void Slider<T>::SetMinValue(const T& minValue)
{
    this->minValue = minValue;
}

template <typename T>
const T& Slider<T>::GetMaxValue() const
{
    return maxValue;
}

template <typename T>
void Slider<T>::SetMaxValue(const T& maxValue)
{
    this->maxValue = maxValue;
}

// template<typename T>
inline void Slider<float>::Render() const
{
    ImGui::DragFloatWithSetter(text.c_str(), getter, setter, speed, minValue, maxValue);
}
