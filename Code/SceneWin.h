#pragma once
#include "Scene.h"
#include "BaseElement.h"
class SceneWin :
    public Scene
{
    BaseElement _Win;
public:
    void reinit();
    void init();
    void update();
    void render();
};

