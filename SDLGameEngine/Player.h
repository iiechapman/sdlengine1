//
//  Player.h
//  SDLGameDevelopmentChapter1
//
//  Created by Evan Chapman on 4/23/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#ifndef __SDLGameDevelopmentChapter1__Player__
#define __SDLGameDevelopmentChapter1__Player__

#include <iostream>
#include <vector>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"


class TileLayer;

//inherit from sdlgameobject
class Player : public SDLGameObject {
public:
    Player();
    Player(GameObjectParams params, int numberFrames);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(GameObjectParams params);
    virtual void collision();
    
    void setCollisionLayers(vector<TileLayer*> collisionLayers){
        m_pCollisionLayers = collisionLayers;
    }
    
private:
    void handleInput();
    void handlePhysics();
    void handleMovement();
    void handleAnimation();
    bool checkCollideTile(Vector2D pos);
    
    Vector2D m_acceleration{0,0};

    bool m_bIsOnGround = false;
    int m_maxJumps = 2;
    int m_numJumps = m_maxJumps;
    bool m_bJumpHeld;
    bool m_bCanJump;
    bool m_bIsJumping;
    bool m_canJump;
    bool m_bIsFalling = true;
    float m_jumpSpeed = 7;
    
    bool m_bIsRunning;
    bool m_bMoveRight;
    bool m_bMoveLeft;

    float m_jetSpeed = 0.15;
    float m_maxFuel = 100;
    float m_currentFuel = 0;
    float m_fuelCost = 1;
    bool  m_bIsJetting = false;
    
    float m_runSpeed = .12;
    float m_walkSpeed = 0.08;

    
    float m_horizontalSpeed = m_runSpeed;
    float m_verticalSpeed = m_jumpSpeed;
    float m_horizontalDrag = .2;
    

    float m_normalGravity = .3;
    float m_jetGravity = 0.1;
    float m_currentGravity = m_normalGravity;
    
    
    vector<TileLayer*> m_pCollisionLayers;

    
};



class PlayerCreator : public BaseCreator{
    GameObject* createGameObject() const{
        return new Player();
    }
    
};



#endif /* defined(__SDLGameDevelopmentChapter1__Player__) */
