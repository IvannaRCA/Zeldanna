#include "InputManager.h"

extern bool gameOn;

InputManager* InputManager::pInstance = nullptr;

InputManager* InputManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new InputManager();
	}
	return pInstance;
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	while (SDL_PollEvent(&_Event))
	{
		switch (_Event.type)
		{
		case SDL_QUIT:
			gameOn = false;
			break;
		case SDL_SCANCODE_ESCAPE:
			gameOn = false;
			break;
		default:
			break;
		}
	}

	pKeyboardStates = SDL_GetKeyboardState(NULL);
}

bool InputManager::IsKeyDown(int scancode)
{
	return pKeyboardStates[scancode];
}



