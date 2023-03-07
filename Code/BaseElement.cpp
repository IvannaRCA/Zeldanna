#include "BaseElement.h"
#include "Video.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Map.h"
#include <stdlib.h>

BaseElement::BaseElement()
{
	_Sprite = 0;
	_Rect = { 0, 0, 0, 0 };
}

BaseElement::~BaseElement()
{
}

void BaseElement::init()
{
	_Sprite = 0;
	_SpriteX = 0;
	_SpriteY = 0;
	_Rect = { 0, 0, 0, 0 };
	_GfxWorld = { 0, 0, 0, 0 };
	_Xreal = 0.0f;
	_Yreal = 0.0f;
	_GfxScreen = { 0, 0, 0, 0 };
}

void BaseElement::render()
{
	Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w, _Rect.h, 0, 0);
}

void BaseElement::render(int w)
{
	Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w * w, _Rect.h, 0, 0);
}

void BaseElement::render(int rPosX, int rPosY)
{
	_GfxScreen.x = Video::getInstance()->getCamX() - _GfxWorld.x;
	_GfxScreen.y = Video::getInstance()->getCamY() - _GfxWorld.y;
	Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w, _Rect.h, _Rect.w * rPosX, _Rect.h * rPosY);
}

void BaseElement::renderNumberAnim(int rPosX, int rPosY)
{
	Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w, _Rect.h, _Rect.w * rPosX, _Rect.h * rPosY);
}

void BaseElement::setWH(int valorW, int valorH)
{
	_Rect.w = valorW;
	_Rect.h = valorH;
	_GfxWorld.w = valorW;
	_GfxWorld.h = valorH;
}

void BaseElement::loadGraphic(const char* file)
{
	_Sprite = ResourceManager::getInstance()->loadAndGetGraphicID(file);
}

void BaseElement::setGraphicID()
{
	ResourceManager::getInstance()->getGraphicSize(_Sprite, &_Rect.w, &_Rect.h);
}

void BaseElement::worldCollision()
{
	int tilePosX = (_GfxWorld.x + _Rect.w / 2);
	int tilePosY = (_GfxWorld.y - 48 + _Rect.h / 2);

	// UP
	if (Map::getInstance()->getTileID(tilePosX / 16, (tilePosY - 8) / 16) != 3 
		&& Map::getInstance()->getTileID(tilePosX / 16, (tilePosY - 8) / 16) != 132
		&& Map::getInstance()->getTileID(tilePosX / 16, (tilePosY - 8) / 16) != 25)
	{
		_GfxWorld.y += 1;
		_Yreal += 1.5f;
		_State = IDLE;
	}
	// DOWN
	else if (Map::getInstance()->getTileID(tilePosX / 16, (tilePosY + 8) / 16) != 3 
			 && Map::getInstance()->getTileID(tilePosX / 16, (tilePosY + 8) / 16) != 132
			 && Map::getInstance()->getTileID(tilePosX / 16, (tilePosY + 8) / 16) != 25)
		 {
			 _GfxWorld.y -= 1;
			 _Yreal = _GfxWorld.y;
			 _State = IDLE;
		 }
	// RIGHT
	else if (Map::getInstance()->getTileID((tilePosX + 8) / 16, (tilePosY) / 16) != 3 
			 && Map::getInstance()->getTileID((tilePosX + 8) / 16, (tilePosY) / 16) != 132
			 && Map::getInstance()->getTileID((tilePosX + 8) / 16, (tilePosY) / 16) != 25)
		 {
		 	 _GfxWorld.x -= 1;
		 	 _Xreal = _GfxWorld.x;
		 	 _State = IDLE;
		 }
	// LEFT
	else if (Map::getInstance()->getTileID((tilePosX - 8) / 16, (tilePosY) / 16) != 3 
			 && Map::getInstance()->getTileID((tilePosX - 8) / 16, (tilePosY) / 16) != 132
			 && Map::getInstance()->getTileID((tilePosX - 8) / 16, (tilePosY) / 16) != 25)
		 {
		 	 _GfxWorld.x += 1;
		 	 _Xreal += 1.5f;
		 	 _State = IDLE;
		 }
}

bool BaseElement::isCollision(mRect* rectA, mRect* rectB)
{
	if ((rectA->x < rectB->x + rectB->w/2) &&
		(rectB->x < rectA->x + rectA->w/2) &&
		(rectA->y < rectB->y + rectB->h/2) &&
		(rectB->y < rectA->y + rectA->h/2)) {
		return true;
	}
	return false;
}


