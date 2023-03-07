#include "ResourceManager.h"
#include "Video.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <iostream>

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager* ResourceManager::getInstance()
{
    if (pInstance == NULL)
    {
        pInstance = new ResourceManager();
    }
    return pInstance;
}

ResourceManager::ResourceManager()
{
    mFirstFreeSlot = 0;
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
    std::map<std::string, Sint32>::iterator it;
    it = mIDMap.find(file);
    int slot = it->second;

	SDL_DestroyTexture(mGraphicsVector.at(slot)); // RAFEL
    mGraphicsVector.at(slot) = NULL;
    mIDMap.erase(it);
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
    for (int i = 0; i < mGraphicsVector.size(); i++)
    {
        if (mGraphicsVector.at(i) == NULL)
        {
            return i;
        }
    }
    return mGraphicsVector.size();
}

Sint32 ResourceManager::addGraphic(const char* file)
{
    mFirstFreeSlot = updateFirstFreeSlotGraphic();
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);

    if ((initted & flags) != flags) {
        std::cout << "Error init SDL_Image" << IMG_GetError() << std::endl;
    }

    SDL_Texture* Image;
	SDL_Renderer* RendererContext = Video::getInstance()->getRenderer(); // RAFEL Pon tu esto correcto de tu clase Video.
    Image = IMG_LoadTexture(RendererContext, file); // RAFEL

    if (Image == NULL)
    {
        std::cout << "Error IMG_Load: " << IMG_GetError() << std::endl;
    }
    else
    {
        if (mGraphicsVector.size() == mFirstFreeSlot)
        {
            mGraphicsVector.push_back(Image);

        }
        else
        {
            // RAFEL Esta linea estaba por encima del IF. Mejor tras verificar que se ha cargado la Imagen.
            mGraphicsVector.at(mFirstFreeSlot) = Image;
        }
        // RAFEL Es preferible darle los tipos correctos a la hora de hacer un pair. 
		// Por eso hago variables primero antes del pair
		std::string nameToSave = file; // RAFEL
		int IDofTexture = mFirstFreeSlot; // RAFEL
        mIDMap.insert(std::pair <std::string, int>(nameToSave, IDofTexture)); // RAFEL
    }
    return mIDMap.find(file)->second;
}


Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
    std::map<std::string, int>::iterator it;
    it = mIDMap.find(file);
    if (it != mIDMap.end())
    {
        return mIDMap.find(file)->second;
    }
    else
    {
        return addGraphic(file);
    }
}

void ResourceManager::getGraphicSize(Sint32 img, int* width, int* height)
{
	// RAFEL En texturas se pregunta a la grafica los datos con
	// SDL_QueryTexture
	SDL_QueryTexture(mGraphicsVector.at(img), NULL, NULL, width, height);
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	int w;
	// RAFEL En texturas se pregunta a la grafica los datos con
	// SDL_QueryTexture
	SDL_QueryTexture(mGraphicsVector.at(img), NULL, NULL, &w, NULL);
    return (Uint16) w;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	int h;
	// RAFEL En texturas se pregunta a la grafica los datos con
	// SDL_QueryTexture
	SDL_QueryTexture(mGraphicsVector.at(img), NULL, NULL, NULL, &h);
	return (Uint16)h;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
    return mGraphicsVector.at(ID);
}
