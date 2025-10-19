#include "pch.h"
#include "Clock.h"


float Clock::Tick()
{
    float duration = 0;
    if (started)
        duration = GetTimeFromLastTick();
    else
        started = true;

    start = std::chrono::steady_clock::now();
    return duration;
}

float Clock::GetTimeFromLastTick() const
{
    if (!started)
        return 0;
    std::chrono::duration<float> duration = std::chrono::steady_clock::now() - start;
    return duration.count();
}

