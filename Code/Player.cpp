#include "Video.h"
#include "InputManager.h"
#include "Definiciones.h"
#include "Player.h"
#include "Timer.h"

extern InputManager* input;
extern Timer* timer;
extern Uint32 global_elapsed_time;

Player::Player()
{
	_FrameTime = 0;
	_MaxLife = 6;
	_Life = 6;
	_Rupee = 0;
	_TriforcePieces = 0;
	_Sword = false;;
	_Attack = false;;
}

Player::~Player()
{
}

void Player::init()
{
	_State = IDLE;
	_Direction = RIGHT;
	_Rect.x = 0;
	_Rect.y = 0;
	_Velocity = 0.07f;
	_SpriteX = 3;
	_SpriteY = 0;
}

void Player::update()
{
	_State = IDLE;
	if (input->IsKeyDown(KEY_DOWN))
	{
		_Direction = DOWN;
		_State = MOVE;
	}
	if (input->IsKeyDown(KEY_UP))
	{
		_Direction = UP;
		_State = MOVE;
	}
	if (input->IsKeyDown(KEY_LEFT))
	{
		_Direction = LEFT;
		_State = MOVE;
	}
	if (input->IsKeyDown(KEY_RIGHT))
	{
		_Direction = RIGHT;
		_State = MOVE;
	}
	if (_Sword)
	{
		if (input->IsKeyDown(KEY_Z))
		{
			_State = ATTACK;
			_Attack = true;
		}
		else
		{
			_Attack = false;
		}
	}

	int _FrameRate = 100;
	switch (_Direction)
	{
	case UP:
		if (_State == MOVE)
		{
			_Yreal -= _Velocity * global_elapsed_time;
			_GfxWorld.y = (int)_Yreal;
			_SpriteX = 2;
			_FrameTime += global_elapsed_time;
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
		}
		else if (_State == ATTACK)
		{
			if (_Sword)
			{
				_SpriteY = 2;
				_SpriteX = 2;
			}
		}
		else
		{
			_SpriteX = 2;
			_SpriteY = 0;
		}
		break;
	case DOWN:
		if (_State == MOVE)
		{
			_Yreal += _Velocity * global_elapsed_time;
			_GfxWorld.y = (int)_Yreal;
			_SpriteX = 0;
			_FrameTime += global_elapsed_time;
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
		}
		else if (_State == ATTACK)
		{
			if (_Sword)
			{
				_SpriteX = 0;
				_SpriteY = 2;
			}
		}
		else
		{
			_SpriteX = 0;
			_SpriteY = 0;
		}
		break;
	case LEFT:
		if (_State == MOVE)
		{
			_Xreal -= _Velocity * global_elapsed_time;
			_GfxWorld.x = (int)_Xreal;
			_SpriteX = 1;
			_FrameTime += global_elapsed_time;
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
		}
		else if (_State == ATTACK)
		{
			if (_Sword)
			{
				_SpriteX = 1;
				_SpriteY = 2;
			}
		}
		else
		{
			_SpriteX = 1;
			_SpriteY = 0;
		}
		break;
	case RIGHT:
		if (_State == MOVE)
		{
			_Xreal += _Velocity * global_elapsed_time;
			_GfxWorld.x = (int)_Xreal;
			_SpriteX = 3;
			_FrameTime += global_elapsed_time;
			if (_FrameTime > _FrameRate)
			{
				_SpriteY++;
				_FrameTime = 0;
			}
			if (_SpriteY > 1) { _SpriteY = 0; }
		}
		else if (_State == ATTACK)
		{
			if (_Sword)
			{
				_SpriteX = 3;
				_SpriteY = 2;
			}
		}
		else
		{
			_SpriteX = 3;
			_SpriteY = 0;
		}
		break;
	default:
		break;
	}
}

void Player::render(int posX, int posY)
{
	_GfxScreen.x = _GfxWorld.x - Video::getInstance()->getCamX();
	_GfxScreen.y = _GfxWorld.y - Video::getInstance()->getCamY();
	Video::getInstance()->renderGraphic(_Sprite, _GfxScreen.x, _GfxScreen.y, _Rect.w, _Rect.h, _Rect.w * posX, _Rect.h * posY);

}
