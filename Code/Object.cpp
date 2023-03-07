#include "Object.h"
#include "Video.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::init()
{
	_Hitten = false;
}

void Object::render()
{
	if (_Hitten == false)
	{
		_GfxScreen.x = _GfxWorld.x - Video::getInstance()->getCamX();
		_GfxScreen.y = _GfxWorld.y - Video::getInstance()->getCamY();
		if (_GfxScreen.y > 48)
			Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w, _Rect.h, 0, 0);
	}
}
