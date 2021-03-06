//
//  SoundManager.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "EventHandler.h"

using namespace std;


/**
 * \class SoundManager
 * \brief Handles sounds and songs in game
 * \author Evan Chapman
 * \version 1
 * Contact: iiechapman\@gmail.com
 */
class SoundManager{
public:
    ~SoundManager();
    
    static SoundManager* Instance();
    
    bool loadSound(string fileName, string soundID);
    bool loadSong(string fileName, string soundID);
    
    void playSong(string ID);
    void playSound(string ID);
    
    void stopSong();
    void stopSound(int channel);
    
    void setSongVolume(int volume);
    
    void clearSoundMap();
    void clean();
    
    void update();
    
private:
    SoundManager();
    static SoundManager* s_pInstance;
    
    map<string, Mix_Music*> m_songMap;
    map<string, Mix_Chunk*> m_soundMap;
    int m_totalChannels = 4;
    int m_currentChannel = 0;
    
    EventHandler m_eventHandler;
};

























































//END