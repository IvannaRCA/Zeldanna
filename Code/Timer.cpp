#include "Timer.h"
#include "SDL.h"

Timer* Timer::pInstance = NULL;

Timer* Timer::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Timer();
	}
	return pInstance;
}

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::start()
{
	_StartTicks = SDL_GetTicks();
	_Ticks = 0;
	_Status = true;
}

void Timer::stop()
{
	if (_Status)
	{
		_Status = false;
		_Ticks += SDL_GetTicks() - _StartTicks;
	}
}

int Timer::getTicks()
{
	_Ticks = SDL_GetTicks() - _StartTicks;
	return _Ticks;
}
