#include "SceneGameOver.h"
#include "SceneDirector.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "Definiciones.h"

extern SceneDirector* scene_director;
extern SoundManager* sound;
extern InputManager* input;
extern bool gameOn;

void SceneGameOver::reinit()
{
    // Music
    sound->playSound(_Music1, "ZELDA/Sound/Music/Game-Over.ogg", -1);
    sound->setSoundVolume(_Music1, 30);

    mReinit = false;
}

void SceneGameOver::init()
{
    _GameOver.init();
    _GameOver.loadGraphic("ZELDA/Scenes/GameOver.jpg");
    _GameOver.setGraphicID();
    _GameOver.setWH(256, 224);                // w-h de cada sprite
    _GameOver.setXY(0, 0);                  // x-y del sprite
    _GameOver.setWorldXY(0, 0);
    _GameOver.setScreenXY(0, 0);
}

void SceneGameOver::update()
{
    if (input->IsKeyDown(KEY_RETURN))
    {
        sound->haltSound(_Music1);
        scene_director->changeScene(GAME);
    }
    if (input->IsKeyDown(KEY_ESCAPE))
    {
        gameOn = false;
    }
}

void SceneGameOver::render()
{
    _GameOver.render();
}
