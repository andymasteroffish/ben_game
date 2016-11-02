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
    
    float speed = 200;
    
    size = 6;
    outOfBoundsSize = 2;
    
    pos.set(x,y);
    vel.x = speed * cos(angle);
    vel.y = speed * sin(angle);
    
    outOfBounds = false;
    killMe = false;
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
    ofSetColor(parent->color);
    ofFill();
    ofDrawCircle(pos.x, pos.y, size);
}
