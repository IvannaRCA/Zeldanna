#include "SceneDirector.h"
#include "SceneIntro.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
#include "SceneWin.h"

SceneDirector* SceneDirector::pInstance = NULL;

SceneDirector* SceneDirector::getInstance(){
	if (!pInstance) {
		pInstance = new SceneDirector();
	}
	return pInstance;
}

SceneDirector::SceneDirector(){
	init();
}

SceneDirector::~SceneDirector(){
}

void SceneDirector::init(){
	mVectorScenes.resize(NUM_SCENES);

	SceneIntro*     intro		= new SceneIntro();
	SceneGame*      game		= new SceneGame();
	SceneGameOver*  gameover	= new SceneGameOver();
	SceneWin*		win			= new SceneWin();

	mVectorScenes[INTRO]		= intro;
	mVectorScenes[GAME]			= game;
	mVectorScenes[GAMEOVER]		= gameover;
	mVectorScenes[WIN]			= win;

	intro->init();
	game->init();
	gameover->init();
	win->init();

	mCurrScene = INTRO;
}

void SceneDirector::changeScene(SceneEnum next_scene, bool reinit){
	mVectorScenes[next_scene]->setReInit(reinit);
	mCurrScene = next_scene;
}
