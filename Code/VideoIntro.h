#pragma once
#include "BaseElement.h"
#include "Timer.h"
#include "Video.h"
#include "InputManager.h"
class VideoIntro :
    public BaseElement
{
public:
    VideoIntro();
    ~VideoIntro();

    void init();
    void update();
    void render(int posX, int posY);
};

