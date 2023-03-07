#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <vector>
#include <string>
#include "SDL.h"

//! ResourceManager class
/*!
	Handles the load and management of the graphics in the game.
*/
class ResourceManager
{
public:

	//! Destructor.
	~ResourceManager();

	//! Deletes a graphic from the ResourceManager map
	/*!
		\param file Filepath to the graphic
	*/
	void removeGraphic(const char* file);


	//! Gets the graphic ID from file name. Use addGraphic if it needs to load image from disc
	/*!
		\param file Filepath to the graphic
		\return ID of the graphic
	*/
	Sint32 loadAndGetGraphicID(const char* file);

	//! Returns width and Height of a Surface
	/*!
	 *	\param img ID texture
	 *	\param width Return variable for width value
	 *	\param height Return variable for height value
	 */
	void getGraphicSize(Sint32 img, int* width, int* height);

	//! Returns width of a Surface
	/*!
	 *	\param img ID texture
	 * 	\return Width of Texture
	 */
	Uint16 getGraphicWidth(Sint32 img);

	//! Returns Height of a Texture
	/*!
	 *	\param img ID texture
	 *  \return Height of Texture
	 */
	Uint16 getGraphicHeight(Sint32 img);

	// RAFEL Cambio a SDL_Texture
	//! Returns the SDL_Texture of the graphic. Only for render methods.
	/*!
		\param ID ID of the graphic
		\return SDL_Texture
	*/
	SDL_Texture* getGraphicByID(Sint32 ID);

	//! Gets Singleton instance
	/*!
		\return Instance of ResourceManager (Singleton).
	*/
	static ResourceManager* getInstance();

protected:
	//! Constructor of an empty ResourceManager.
	ResourceManager();

private:

	//! Loads from disc and adds a graphic to the ResourceManager 
	/*!
		\param file Filepath to the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 addGraphic(const char* file);

	//! Searches the first NULL in mGraphicsVector and updates mFirstFreeSlot to store its position
	/*!
		\return Index of the first NULL in mGraphicsVectorTexture
	*/
	Uint32 updateFirstFreeSlotGraphic();

	// RAFEL Cambio a SDL_Texture
	std::vector<SDL_Texture*>	mGraphicsVector;	/*!<  Vector that stores Textures. Useful in render methods and sequential access*/
	std::map<std::string, Sint32>	mIDMap;			/*!<  Map that stores ID. Links strings to ID, Useful for check if graphic is has been loaded previously*/
	Uint32				mFirstFreeSlot;		/*!<  First free slot in the mGraphicsVector*/
	static ResourceManager* pInstance;		/*!<  Singleton instance*/
};

#endif
