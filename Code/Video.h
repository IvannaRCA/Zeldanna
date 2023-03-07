#pragma once
#include <SDL.h>

class Video
{
	struct Cam {
		int x, y, w, h;
	};
	Cam _Camera;
	Video();
	static Video* unica_instancia;
public:
	~Video();

	static Video* getInstance()
	{
		if (unica_instancia == NULL)
			unica_instancia = new Video();

		return unica_instancia;
	}

	// Camera
	void setCamX(int value) { _Camera.x = value; };
	void setCamY(int value) { _Camera.y = value; };
	int  getCamX() { return _Camera.x; };
	int  getCamY() { return _Camera.y; };
	int  getCamW() { return _Camera.w; };
	int  getCamH() { return _Camera.h; };

	void renderGraphic(int img, int posX, int posY, int width, int height, int rPosX, int rPosY);
	void clearScreen(int r, int g, int b, int a);
	void updateScreen();
	SDL_Renderer* getRenderer() { return gRenderer; };
	void waitTime(int ms);
	void close();
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
};

