#include <SDL.h>
#include "Video.h"
#include "ResourceManager.h"
#include "Definiciones.h"

Video* Video::unica_instancia = NULL;

Video::Video()
{
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, 
								SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(gRenderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

	_Camera.x = 0;
	_Camera.y = 0;
	_Camera.w = 256;
	_Camera.h = 176;
}

Video::~Video()
{
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height, int rPosX, int rPosY)
{
	SDL_Rect rSource, rDestiny;
	rSource.h = height;
	rSource.w = width;
	rSource.x = rPosX;
	rSource.y = rPosY;
	rDestiny.h = height;
	rDestiny.w = width;
	rDestiny.x = posX;
	rDestiny.y = posY;
	SDL_Texture* texture = ResourceManager::getInstance()->getGraphicByID(img);
	SDL_RenderCopy(gRenderer, texture, &rSource, &rDestiny);
}

void Video::clearScreen(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
	SDL_RenderClear(gRenderer);
}

void Video::updateScreen()
{
	SDL_RenderPresent(gRenderer);
}

void Video::waitTime(int ms)
{
	SDL_Delay(ms);
}

void Video::close()
{
	SDL_DestroyWindow(gWindow);
}
