#pragma once
#include <map>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_Mixer.h"

using namespace std;

class SoundManager
{
public:
	~SoundManager();
	void removeSound(const char* file);
	Sint32 loadAndGetSoundID(const char* file);
	void haltSound(int channel);
	void resumeSound(int channel);
	void pauseSound(int channel);
	void setSoundVolume(int channel, int volume);	// -1 in channel will set the volume for all allocated channels.
	void playSound(int channel, const char* file, int loops);
	bool isPlaying(int channel);
	static SoundManager* getIntance();
protected:
	SoundManager();
private:
	Uint32				 updateFirstFreeSlotSound();
	Sint32				 addSound(const char* file);
	vector<Mix_Chunk*>   mSoundVector;
	map<string, Sint32>  mIDMap;
	Uint32				 mFirstFreeSlot;
	static SoundManager* pInstance;
};

