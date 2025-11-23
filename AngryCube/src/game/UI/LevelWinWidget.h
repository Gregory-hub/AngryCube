#pragma once
#include "engine/UI/Widget.h"


class LevelWinWidget : public Widget
{
private:
    bool isActive = false;
    glm::vec2 position;

public:
    LevelWinWidget();

    bool IsActive() const;
    void Activate();
    void Deactivate();

    void Render() const override;
    void Reset() override;

private:
    void OnButtonQuitPressed() const;
    void OnButtonRestartPressed() const;
    void OnButtonNextPressed() const;
};
