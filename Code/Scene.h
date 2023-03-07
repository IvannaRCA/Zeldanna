#ifndef SCENE_H
#define SCENE_H

//! Scene class
/*!
	Handles the Scenes for all the game. (loop de escenas, uso de virtual)
*/
class Scene
{
	public:
		//! Constructor of an empty Scene.
		Scene();

		//! Destructor
		virtual ~Scene();

		//! Initializes the Scene.
		virtual void init();	// visrtual para usar las funciones del hijo

		//! Function to withdraw anything owned by the class and to call init
		virtual void reinit();

		//! Handles the updating of the scene
		virtual void update() {};

		//! Handles the drawing of the scene
		virtual void render() {};


		void setReInit(bool loaded = true)	{mReinit = loaded;};
		bool mustReInit()				{return mReinit;};

	protected:
		bool		mReinit;			/*!<  Reload when returning to scene*/
		int			_Music1;
};

#endif
