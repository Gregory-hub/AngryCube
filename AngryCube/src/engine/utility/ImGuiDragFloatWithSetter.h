#pragma once


namespace ImGui
{
template <typename Getter, typename Setter>
void DragFloatWithSetter(const char* label, Getter getter, Setter setter, float speed = 1.0f, float min = 0.0f, float max = 0.0f, const char* format = "%.3f") {
    // 1. Get the current value from the getter
    float currentValue = getter();
    float newValue = currentValue;

    // 2. Call the standard ImGui::DragFloat, which will modify `newValue`
    ImGui::DragFloat(label, &newValue, speed, min, max, format);

    // 3. Check if the value has changed and call the setter
    if (currentValue != newValue) {
        setter(newValue);
    }
}
}
