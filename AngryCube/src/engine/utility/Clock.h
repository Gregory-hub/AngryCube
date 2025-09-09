#pragma once

#include <chrono>


class Clock
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start;
	bool started = false;

public:
	float Tick();
	float GetTimeFromLastTick() const;
};

