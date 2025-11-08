#pragma once

// Class for processing user input
class PlayerController
{
public:
    virtual ~PlayerController() = 0;
};

inline PlayerController::~PlayerController() = default;
