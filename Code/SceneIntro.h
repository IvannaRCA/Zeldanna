#pragma once
#include "VideoIntro.h"

#include "Scene.h"

class SceneIntro :
    public Scene
{
    VideoIntro _Video;

public:

    void reinit();
    void init();
    void update();
    void render();
};

