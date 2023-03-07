#pragma once
#include "SDL.h"


class InputManager
{
	SDL_Event _Event;
	const Uint8* pKeyboardStates;
	static InputManager* pInstance;
	InputManager();
public:
	~InputManager();

	void update();

	bool IsKeyDown(int scancode);
	static InputManager* getInstance();
};

