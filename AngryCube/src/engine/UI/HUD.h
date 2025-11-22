#pragma once
#include "Widget.h"

class HUD
{
public:
    virtual ~HUD() = 0;

    virtual void Reset() = 0;
    virtual void Render() const = 0;
};

inline HUD::~HUD() = default;
