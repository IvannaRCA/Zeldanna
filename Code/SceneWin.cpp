#include "SceneWin.h"
#include "SceneDirector.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "Definiciones.h"

extern SceneDirector* scene_director;
extern SoundManager* sound;
extern InputManager* input;
extern bool gameOn;

void SceneWin::reinit()
{
    // Music
    sound->playSound(_Music1, "ZELDA/Sound/Music/Ending.ogg", -1);
    sound->setSoundVolume(_Music1, 30);

    mReinit = false;
}

void SceneWin::init()
{
    _Win.init();
    _Win.loadGraphic("ZELDA/Scenes/Win.jpg");
    _Win.setGraphicID();
    _Win.setWH(256, 224);                // w-h de cada sprite
    _Win.setXY(0, 0);                  // x-y del sprite
    _Win.setWorldXY(0, 0);
    _Win.setScreenXY(0, 0);
}

void SceneWin::update()
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

void SceneWin::render()
{
    _Win.render();
}
