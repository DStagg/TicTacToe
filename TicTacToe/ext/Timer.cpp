#include "Timer.h"

Timer::Timer()
{
	Reset();
}

void Timer::Reset()
{
	_PrevTicks = (float)SDL_GetTicks();
}

float Timer::GetSec()
{
	return ((float)SDL_GetTicks() - _PrevTicks) / 1000.0f;
}

float Timer::Lap()
{
	float now = (float)SDL_GetTicks();
	float dt = now - _PrevTicks;
	_PrevTicks = now;
	return dt;
}