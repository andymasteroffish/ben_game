//
//  Bullet.hpp
//  emptyExample
//
//  Created by Andrew Wallace on 11/1/16.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "ofMain.h"
#include "Player.hpp"

class Bullet{
public:
    
    
    
    void setup(float x, float y, float angle, Player * _parent);
    void update(float deltaTime, float arenaSize);
    void draw();
    
    
    ofVec2f pos;
    ofVec2f vel;
    
    float size;
    float outOfBoundsSize;
    
    bool outOfBounds;
    bool killMe;
    
    Player * parent;
    
    float displayAngle;
    
};

#endif /* Bullet_hpp */
