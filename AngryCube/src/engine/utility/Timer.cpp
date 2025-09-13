#include "Timer.h"


void Timer::Start()
{
	start = std::chrono::steady_clock::now();
}

float Timer::End()
{
	std::chrono::duration<float> duration = std::chrono::steady_clock::now() - start;
	return duration.count();
}

