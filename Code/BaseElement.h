#pragma once
#include <string>

enum State { IDLE, MOVE, ATTACK, HURT, DEAD };
enum Direction { UP, DOWN, LEFT, RIGHT };

class BaseElement
{
protected:
	State _State;
	Direction _Direction;

	int _FrameTime;
	float _Velocity;
	int _Sprite;
	int _SpriteX;
	int _SpriteY;
	struct mRect {
		int x, y, w, h;
	};
	float _Xreal;
	float _Yreal;
	mRect _Rect;
	mRect _GfxWorld;
	mRect _GfxScreen;
public:
	BaseElement();
	~BaseElement();

	void init();

	// normal render without camera
	void render();
	// change rendering wifth
	void render(int w);
	// x and y sprite rendering
	void render(int rPosX, int rPosY);
	// rendering number animations
	void renderNumberAnim(int rPosX, int rPosY);

	// _Rect (image)
	int getX() { return _GfxWorld.x; };
	int getY() { return _GfxWorld.y; };
	void setX(int valor) { _Rect.x = valor; };
	void setY(int valor) { _Rect.y = valor; };
	void setXY(int valorX, int valorY) { _Rect.x = valorX; _Rect.y = valorY; };
	void setWH(int valorW, int valorH);
	int getW() { return _Rect.w; };
	int getH() { return _Rect.h; };
	void setWorldXY(int x, int y) { _GfxWorld.x = x; _GfxWorld.y = y; _Xreal = x; _Yreal = y; };
	void setScreenXY(int x, int y) { _GfxScreen.x = x; _GfxScreen.y = y; };

	void loadGraphic(const char* file);
	void setGraphicID();
	int getGraphicID() { return _Sprite; };
	int getSpriteX() { return _SpriteX; };
	int getSpriteY() { return _SpriteY; };
	void setSpriteX(int sprite) { _SpriteX = sprite; };
	void setSpriteY(int sprite) { _SpriteY = sprite; };

	// _State
	void setState(State state) { _State = state; };
	State getState() { return _State; };

	// Direction
	void setDirection(Direction dir) { _Direction = dir; };
	Direction getDirection() { return _Direction; };

	// Collision
	mRect* getRect() { return &_GfxWorld; };
	void worldCollision();
	bool isCollision(mRect* rectA, mRect* rectB);
};

