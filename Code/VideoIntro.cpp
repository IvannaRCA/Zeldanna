#include "VideoIntro.h"
#include "Timer.h"
#include <iostream>
extern Timer* timer;
extern Uint32 global_elapsed_time;

VideoIntro::VideoIntro()
{
}

VideoIntro::~VideoIntro()
{
}

void VideoIntro::init()
{
	_Rect.x = 0;
	_Rect.y = 0;
	_SpriteX = 0;
	_FrameTime = 0;
}

void VideoIntro::update()
{
	int _FrameRate = 50;
	_FrameTime += global_elapsed_time;
	if (_FrameTime > _FrameRate)
	{
		_SpriteX++;
		_FrameTime = 0;
	}
	if (_SpriteX > 11) { _SpriteX = 0; }
}

void VideoIntro::render(int posX, int posY)
{
	Video::getInstance()->renderGraphic(_Sprite, _Rect.x, _Rect.y, _Rect.w, _Rect.h, _Rect.w * posX, _Rect.h * posY);
}
