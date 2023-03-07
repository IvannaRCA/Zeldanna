#include "Enemy.h"
#include "Video.h"
#include "Timer.h"
#include "Definiciones.h"

extern Timer* timer;
extern Uint32 global_elapsed_time;

Enemy::Enemy()
{
	_FrameTime = 0;
	_State = IDLE;
	_Direction = DOWN;
	_Life = 0;
	_IsDead = false;
	_Rand = 0;
	exit = false;
}

Enemy::~Enemy()
{
}

void Enemy::init()
{
	_Life = 0;
	_SpriteX = 0;
	_SpriteY = 0;
	_Velocity = 0.07f;
}

void Enemy::update()
{
	int _FrameRate = 1000;
	int _FrameRate2 = 1500;
	_FrameTime += global_elapsed_time;
	if (_FrameTime > _FrameRate)
	{
		if (!exit)
		{
			_Rand = rand() % 5 + 1;
			exit = true;
		}
	}
	else
	{
		_Rand = 5;
	}
	switch (_Rand)
	{
	case 1:
		// UP
		if (_GfxScreen.y > UP_LIMIT)
		{
			_State = MOVE;
			_Direction = UP;
			_SpriteX = 2;
			/*
			_FrameTime += timer->getTicks();
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
			*/
			if (_FrameTime > _FrameRate2)
			{
				_FrameTime = 0;
				exit = false;
			}
		}
		else
		{
			_State = IDLE;
		}
		break;
	case 2:
		// DOWN
		if (_GfxScreen.y < DOWN_LIMIT)
		{
			_State = MOVE;
			_Direction = DOWN;
			_SpriteX = 0;
			/*
			_FrameTime += timer->getTicks();
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
			*/
			if (_FrameTime > _FrameRate2)
			{
				_FrameTime = 0;
				exit = false;
			}
		}
		else
		{
			_State = IDLE;
		}
		break;
	case 3:
		// RIGHT
		if (_GfxScreen.x < RIGHT_LIMIT)
		{
			_State = MOVE;
			_Direction = RIGHT;
			_SpriteX = 3;
			/*
			_FrameTime += timer->getTicks();
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
			*/
			if (_FrameTime > _FrameRate2)
			{
				_FrameTime = 0;
				exit = false;
			}
		}
		else
		{
			_State = IDLE;
		}
		break;
	case 4:
		// LEFT
		if (_GfxScreen.x > LEFT_LIMIT)
		{
			_State = MOVE;
			_Direction = LEFT;
			_SpriteX = 1;
			/*
			_FrameTime += timer->getTicks();
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
			*/
			if (_FrameTime > _FrameRate2)
			{ 
				_FrameTime = 0;
				exit = false;
			}
		}
		else 
		{
			_State = IDLE;
		}
		break;
	case 5:
		_State = IDLE;
		_SpriteY = 0;
		if (_FrameTime > _FrameRate2)
		{
			_FrameTime = 0;
			exit = false;
		}
		break;
	default:
		break;
	}


	if (_State == MOVE && _Direction == DOWN)
	{
			_Yreal += _Velocity * global_elapsed_time;
			_GfxWorld.y = (int)_Yreal;
	}
	if (_State == MOVE && _Direction == UP)
	{
		_Yreal -= _Velocity * global_elapsed_time;
		_GfxWorld.y = (int)_Yreal;
	}
	if (_State == MOVE && _Direction == LEFT)
	{
		_Xreal -= _Velocity * global_elapsed_time;
		_GfxWorld.x = (int)_Xreal;
	}
	if (_State == MOVE && _Direction == RIGHT)
	{
		_Xreal += _Velocity * global_elapsed_time;
		_GfxWorld.x = (int)_Xreal;
	}

	if (_Life <= 0)
	{
		_IsDead = true;
	}
}

void Enemy::render(int rPosX, int rPosY)
{
	_GfxScreen.x = _GfxWorld.x - Video::getInstance()->getCamX();
	_GfxScreen.y = _GfxWorld.y - Video::getInstance()->getCamY();
	if (_GfxScreen.y > 48 && _Yreal > 48)
	{
		if (!_IsDead)
		{
			Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w, _Rect.h, _Rect.w * rPosX, _Rect.h * rPosY);
		}
	}
}
