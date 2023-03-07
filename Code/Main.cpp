#include "SceneDirector.h"
#include "SceneIntro.h"
#include "SceneGame.h"
#include "Timer.h"
#include "Video.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "Definiciones.h"
#include <ctime>
#include <stdlib.h>

SceneDirector*	scene_director = NULL;
Video*			video = NULL;
InputManager*	input = NULL;
SoundManager*	sound = SoundManager::getIntance();
Map*			mapa = Map::getInstance();
Timer*			timer = Timer::getInstance();
Uint32 			global_elapsed_time = 0;
bool			gameOn;

int main(int argc, char* args[])
{
	// Init random
	srand((unsigned)time(NULL));

	// Init Singletons
	scene_director = SceneDirector::getInstance();
	video = Video::getInstance();
	input = InputManager::getInstance();
	gameOn = true;

	// INIT
	timer->start();
	Uint32 last_time = 0;
	while (gameOn)
	{
		// ReInit o no
		if (scene_director->getCurrentScene()->mustReInit()) {
			scene_director->getCurrentScene()->reinit();
		}

		// UPDATE
			//Update time
		Uint32 actualtime = timer->getTicks();
		global_elapsed_time = actualtime - last_time;
		last_time = actualtime;
			
			// Updae input
		input->update();
		
			// Update scene
		scene_director->getCurrentScene()->update();

		// RENDER
		video->clearScreen(0, 0, 0, 0);
		if (!scene_director->getCurrentScene()->mustReInit()) {
			scene_director->getCurrentScene()->render();
		}
		video->updateScreen();
	}

	video->close();
	return 0;
}