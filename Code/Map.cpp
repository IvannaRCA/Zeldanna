#include "Map.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Definiciones.h"

Map* Map::pInstance = NULL;

Map::Map()
{
}

Map::~Map()
{
}

Map* Map::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Map();
	}
	return pInstance;
}

void Map::init()
{
	_Doc.Clear();
	_File = nullptr;
	_RectS = { 0,0,0,0 };
	_RectT = { 0,0,0,0 };
	_IDMap = 0;
	_ID = 0;
	_CellX = 0;
	_CellY = 0;
	_Player = nullptr;
	for (size_t i = 0; i < mapH; i++)
	{
		for (size_t j = 0; j < mapW; j++)
		{
			_TileMap[i][j] = 0;
		}
	}
}

void Map::setMap()
{
	XMLElement* root = _Doc.FirstChildElement();
	for (XMLElement* element = root->FirstChildElement("layer");
		element; element = element->NextSiblingElement("layer"))
	{
		// contenido del tag data
		XMLElement* data = element->FirstChildElement("data");
		string tile = data->GetText();
		int find = tile.find(",");
		int pos = 0;

		// guardar el contenido en un array
		for (int i = 0; i < mapH; i++)
		{
			for (int j = 0; j < mapW; j++)
			{	// 0 a 2 -0 = 0 y 1 -> array
				string tmp = tile.substr(pos, (find - pos));

				_TileMap[i][j] = stoi(tmp);	// pasarlo a int

				pos = find + 1; // pos 0 pasa a ser pos 2+1
				find = tile.find(",", pos); // buscar coma a partir de posicion 3

			}
		}
	}
}

void Map::render()
{
	Video::getInstance()->setCamX(((_Player->getX() + 12) / Video::getInstance()->getCamW()) * 256);
	Video::getInstance()->setCamY(((_Player->getY() - 35) / Video::getInstance()->getCamH()) * 176);
	int _BlockX = Video::getInstance()->getCamX() / 16;
	int _BlockY = Video::getInstance()->getCamY() / 16;

	for (int i = _BlockY; i < _BlockY + 11; i++)
	{
		for (int j = _BlockX; j < _BlockX + 16; j++)
		{
			_RectT.x = j * tileW;
		 	_RectT.y = i * tileH;
			_RectT.w = tileW;
			_RectT.h = tileH;
			_ID = _TileMap[i][j] - 1;	// IMPORTANTE "-1"
			if (_ID >= 0)
			{
				_CellX = _ID % 18;		// columna 
				_CellY = _ID / 18;		// fila
				_RectS.x = _CellX * tileW + tileSP * _CellX + 1;
				_RectS.y = _CellY * tileH + tileSP * _CellY + 1;
				_RectS.w = tileW;
				_RectS.h = tileH;
				_RectT.x = _RectT.x - Video::getInstance()->getCamX();
				_RectT.y = _RectT.y - Video::getInstance()->getCamY() + 48;
				Video::getInstance()->renderGraphic(_IDMap, _RectT.x, _RectT.y, _RectS.w, _RectS.h, _RectS.x, _RectS.y);
			}
		}
	}
}

int Map::getTileID(int tileX, int tileY)
{
	return _TileMap[tileY][tileX];
}

void Map::setFileMap(const char* file)
{
	_File = file;
	_Doc.LoadFile(_File);
	if (_Doc.LoadFile(_File) != XML_SUCCESS)
	{
		cout << "Error XML: " << _Doc.ErrorStr() << endl;
		return;
	}
}

void Map::setTileset(const char* file)
{
	_IDMap = ResourceManager::getInstance()->loadAndGetGraphicID(file);
}
