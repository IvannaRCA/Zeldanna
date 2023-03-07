#pragma once
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Definiciones.h"
#include "Player.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
using namespace tinyxml2;



class Map
{
	XMLDocument _Doc;
	const char* _File;
	struct Rect
	{
		int x, y, w, h;
	};
	Rect _RectS, _RectT;
	int _IDMap;
	int _ID, _CellX, _CellY;
	int _TileMap[mapH][mapW];
	Player* _Player;
	Map();
	static Map* pInstance;
public:
	~Map();
	static Map* getInstance();

	void init();
	void setMap();
	void render();

	int getTileID(int tileX, int tileY);

	void setFileMap(const char* file);
	void setTileset(const char* file);

	void setPlayerObject(Player* player) { _Player = player;; };
};

