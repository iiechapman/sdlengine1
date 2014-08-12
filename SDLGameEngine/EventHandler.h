//
//  EventHandler.h
//  SDLGameEngine
//
//  Created by Evan Chapman on 8/3/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameEngine__EventHandler__
#define __SDLGameEngine__EventHandler__

#include <iostream>
#include <vector>
#include "GameObject.h"

using namespace std;

class EventHandler{
public:
    static EventHandler* Instance();
    ~EventHandler();
    
    void HandleEvent(string event);
    
private:
    EventHandler();
    static EventHandler* s_pInstance;
    
    vector<GameObject*> m_eventResponders;
    
};



#endif /* defined(__SDLGameEngine__EventHandler__) */
