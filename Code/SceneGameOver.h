#pragma once
#include "Scene.h"
#include "BaseElement.h"
class SceneGameOver :
    public Scene
{
    BaseElement _GameOver;
public:
    void reinit();
    void init();
    void update();
    void render();
};

