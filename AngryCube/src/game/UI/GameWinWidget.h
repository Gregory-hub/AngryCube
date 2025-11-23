#pragma once
#include "engine/UI/Widget.h"

class GameWinWidget : public Widget
{
private:
    bool isActive = false;
    glm::vec2 position;

public:
    GameWinWidget();

    bool IsActive() const;
    void Activate();
    void Deactivate();

    void Render() const override;
    void Reset() override;

private:
    void OnButtonQuitPressed() const;
};
