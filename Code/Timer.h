#pragma once

class Timer
{
	int _StartTicks;
	int _Ticks;
	bool _Status;
	static Timer* pInstance;
	Timer();
public:
	static Timer* getInstance();
	~Timer();

	// starts counting time
	void start();
	// stops counting
	void stop();
	// returs the difference between frames since started
	int getTicks();
};

