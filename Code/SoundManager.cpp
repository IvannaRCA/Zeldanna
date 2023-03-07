#include "SoundManager.h"
#include <iostream>
SoundManager* SoundManager::pInstance = NULL;

SoundManager* SoundManager::getIntance()
{
    if (pInstance == NULL)
    {
        pInstance = new SoundManager();
        return pInstance;
    }
}

SoundManager::SoundManager()
{
    mFirstFreeSlot = 0;
}

SoundManager::~SoundManager()
{
}

void SoundManager::removeSound(const char* file)
{
    std::map<std::string, Sint32>::iterator it;
    it = mIDMap.find(file);
    int slot = it->second;

    mSoundVector.at(slot) = NULL;
    mIDMap.erase(it);
}

Sint32 SoundManager::loadAndGetSoundID(const char* file)
{
    std::map<std::string, int>::iterator it;
    it = mIDMap.find(file);
    if (it != mIDMap.end())
    {
        return mIDMap.find(file)->second;
    }
    else
    {
        return addSound(file);
    }
}

void SoundManager::haltSound(int channel)
{
    Mix_HaltChannel(channel);
}

void SoundManager::resumeSound(int channel)
{
    Mix_Resume(channel);
}

void SoundManager::pauseSound(int channel)
{
    Mix_Pause(channel);
}

void SoundManager::setSoundVolume(int channel, int volume)
{
    Mix_Volume(channel, volume);
}

void SoundManager::playSound(int channel, const char* file, int loops)
{
    std::map<std::string, int>::iterator it;
    it = mIDMap.find(file);
    Mix_PlayChannel(channel, mSoundVector.at(it->second), loops);
}

bool SoundManager::isPlaying(int channel)
{
    if (Mix_Playing(channel))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Uint32 SoundManager::updateFirstFreeSlotSound()
{
    for (int i = 0; i < mSoundVector.size(); i++)
    {
        if (mSoundVector.at(i) == NULL)
        {
            return i;
        }
    }
    if (mSoundVector.size() != 0)
    {
        return mSoundVector.size();
    }
    else return 0;
}

Sint32 SoundManager::addSound(const char* file)
{
    mFirstFreeSlot = updateFirstFreeSlotSound();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(128);
    Mix_Chunk* sound;
    sound = Mix_LoadWAV(file);
    if (sound == NULL)
    {
        std::cout << "ERROR Sound Load: " << Mix_GetError() << std::endl;
    }
    else
    {
        if (mSoundVector.size() == mFirstFreeSlot)
        {
            mSoundVector.push_back(sound);

        }
        else
        {
            mSoundVector.at(mFirstFreeSlot) = sound;
        }
        std::string nameToSave = file;
        int IDofSound = mFirstFreeSlot;
        mIDMap.insert(std::pair <std::string, int>(nameToSave, IDofSound));
    }
    return mIDMap.find(file)->second;
}
