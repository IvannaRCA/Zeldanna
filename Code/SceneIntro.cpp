#include "SceneIntro.h"
#include "Definiciones.h"
#include "SceneDirector.h"
#include "InputManager.h"
#include "SoundManager.h"

extern SceneDirector* scene_director;
extern SoundManager* sound;
extern InputManager* input;
extern bool gameOn;

void SceneIntro::reinit()
{
	sound->playSound(_Music1, "ZELDA/Sound/Music/Intro.ogg", -1);
	sound->setSoundVolume(_Music1, 30);

	mReinit = false;
}

void SceneIntro::init()
{
	_Video.init();
	_Video.loadGraphic("ZELDA/Scenes/IntroSpriteSheet.jpg");
	_Video.setGraphicID();
	_Video.setWH(256, 224);        // w-h de cada sprite
	_Video.setXY(0, 0);            // x-y del sprite
	sound->getIntance();
	_Music1 = sound->loadAndGetSoundID("ZELDA/Sound/Music/Intro.ogg");
	_Music1 = sound->loadAndGetSoundID("ZELDA/Sound/Music/Overworld.ogg");
	_Music1 = sound->loadAndGetSoundID("ZELDA/Sound/Music/Game-Over.ogg");
	_Music1 = sound->loadAndGetSoundID("ZELDA/Sound/Music/Ending.ogg");
}

void SceneIntro::update()
{
	_Video.update();
	if (input->IsKeyDown(KEY_RETURN))
	{
		sound->haltSound(_Music1);
		scene_director->changeScene(GAME);
	}
	if (input->IsKeyDown(KEY_ESCAPE))
	{
		sound->haltSound(_Music1);
		gameOn = false;
	}
}

void SceneIntro::render()
{
	_Video.render(_Video.getSpriteX(), _Video.getSpriteY());
}
