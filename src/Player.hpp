//
//  Player.hpp
//  emptyExample
//
//  Created by Andrew Wallace on 11/1/16.
//
//

#ifndef Player_hpp
#define Player_hpp

#include  "ofMain.h"

class Player{
public:
    
    void setup(int idNum, float _distFromCenter);
    void update(float deltaTime, float deathAngle1, float deathAngle2);
    void draw();
    void drawPaddle();
    void buttonPress();
    
    bool checkIfAngleIsInside(float otherAngle);
    void getHit();
    
    ofColor color;
    
    float curAngle;
    
    
    float curWidth; //in radians
    float targetWidth;
    float widthZeno;
    
    
    float speed;    //in radians/sec
    int curDir;
    
    float dashTime;
    float dashTimer;
    float maxDashSpeedBonus;
    
    float widthIncreaseOnFire;
    float widthIncreaseOnHit;
    float widthDecreasePerSec;
    
    float minWidth;
    
    float distFromCenter;
    float height;
    
    bool isDead;
    
    float shootEffectTime;
    float shootEffectTimer;
    
};

#endif /* Player_hpp */
