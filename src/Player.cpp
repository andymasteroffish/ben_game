//
//  Player.cpp
//  emptyExample
//
//  Created by Andrew Wallace on 11/1/16.
//
//

#include "Player.hpp"


void Player::setup(int idNum, float _distFromCenter){
    
    if (idNum == 0){
        color.set(10,140,50);
    }
    if (idNum == 1){
        color.set(50,10,140);
    }
    
    distFromCenter = _distFromCenter;
    height = 20;
    
    curAngle = idNum * PI + PI/2;
    
    curWidth = PI/4;
    targetWidth = curWidth;
    widthZeno = 0.9;
    
    speed = PI/4;
    curDir = 1;
    
    minWidth = PI/20;
    widthIncreaseOnFire = PI/16;
    widthIncreaseOnHit = PI/8;
    
    widthDecreasePerSec = PI/20;
    
    maxDashSpeedBonus = 3;
    dashTime = 0.3;
    dashTimer = 0;
    
}

void Player::update(float deltaTime, float deathAngle){
    
    //shrink them
    targetWidth -= widthDecreasePerSec * deltaTime;
    targetWidth = MAX(targetWidth, minWidth);
    
    //zeno the width
    curWidth = widthZeno*curWidth + (1-widthZeno) * targetWidth;
    
    //move them
    float thisDashBonus = ofMap(dashTimer, dashTime, 0, maxDashSpeedBonus, 1, true);
    curAngle += speed * curDir * deltaTime * thisDashBonus;
    if (curAngle < 0){
        curAngle += TWO_PI;
    }
    if (curAngle > TWO_PI){
        curAngle -= TWO_PI;
    }
    
    dashTimer -= deltaTime;
    
    //is this fool dead?
    isDead = checkIfAngleIsInside(deathAngle) || checkIfAngleIsInside(deathAngle+PI);
    
    
    
    
}

void Player::draw(){
    
    ofSetColor(color);
    if (isDead){
        ofSetColor(140, 50, 10);
    }
    ofFill();
    
    float startAngle = curAngle - curWidth/2;
    float endAngle = curAngle + curWidth/2;
    
    //float angleStep = PI/32;
    
    int numPoints = curWidth * 20;// curWidth/angleStep;
    numPoints = MAX(numPoints, 2);
    //cout<<"numPoints "<<numPoints<<endl;
    
    ofBeginShape();
    
    //inner layer
    for  (int i=0; i<numPoints; i++){
        float thisAngle = ofMap(i, 0, numPoints-1, startAngle, endAngle);
        float thisX = cos(thisAngle) * (distFromCenter+height/2);
        float thisY = sin(thisAngle) * (distFromCenter+height/2);
        ofVertex(thisX, thisY);
        //ofDrawCircle(thisX, thisY, 2);
    }
    
    //outer layer
    for  (int i=numPoints-1; i>=0; i--){
        float thisAngle = ofMap(i, 0, numPoints-1, startAngle, endAngle);
        float thisX = cos(thisAngle) * (distFromCenter-height/2);
        float thisY = sin(thisAngle) * (distFromCenter-height/2);
        ofVertex(thisX, thisY);
        //ofDrawCircle(thisX, thisY, 2);
    }
    
    ofEndShape();
    
}

void Player::buttonPress(){
    curDir *= -1;
    targetWidth += widthIncreaseOnFire;
    dashTimer = dashTime;
}

bool Player::checkIfAngleIsInside(float otherAngle){
    
    //check one side
    float angleA = curAngle + curWidth/2;
    float angleB = curAngle - curWidth/2;
    
    for (int i=-1; i<=1; i++){
        float adjust = i * TWO_PI;
        if ( ( (curAngle+adjust)-otherAngle > 0) != ((angleA+adjust)-otherAngle > 0)){
            return true;
        }
        if ( ( (curAngle+adjust)-otherAngle > 0) != ((angleB+adjust)-otherAngle > 0)){
            return true;
        }
    }
}

void Player::getHit(){
    targetWidth += widthIncreaseOnHit;
}
