#pragma once
#include <SDL3/SDL.h>

class Timer
{
public:

	Timer();
	~Timer() {};

	void Reset();
	float Lap();
	float GetSec();

private:

	float _PrevTicks;
};
