//
//  Bullet.cpp
//  emptyExample
//
//  Created by Andrew Wallace on 11/1/16.
//
//

#include "Bullet.hpp"

void Bullet::setup(float x, float y, float angle, Player * _parent){
    parent = _parent;
    
    float speed = 150;
    
    size = 6;
    outOfBoundsSize = 2;
    
    pos.set(x,y);
    vel.x = speed * cos(angle);
    vel.y = speed * sin(angle);
    
    outOfBounds = false;
    killMe = false;
    
    displayAngle = ofRadToDeg(angle);
}

void Bullet::update(float deltaTime, float arenaSize){
    pos += vel * deltaTime;
    
    if ( ofDistSquared(0, 0, pos.x, pos.y) > arenaSize * arenaSize){
        outOfBounds = true;
        float zeno = 0.75;
        size = zeno * size  + (1.0-zeno) * outOfBoundsSize;
    }
    
    if ( ofDistSquared(0, 0, pos.x, pos.y) > ofGetWidth() * ofGetWidth()){
        killMe = true;
    }
    
}

void Bullet::draw(){
    
    for (int i=0; i<2; i++){
        if (i==0){
            ofSetColor(parent->color);
            ofFill();
        }else{
            ofSetColor(230);
            ofNoFill();
        }
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotate(displayAngle);
        ofSetCircleResolution(3);
        ofDrawCircle(0,0, size);
        ofPopMatrix();
    }
}
