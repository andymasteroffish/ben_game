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
    
    curWidth = PI/6;
    targetWidth = curWidth;
    widthZeno = 0.9;
    
    speed = PI/6;
    curDir = 1;
    
    minWidth = PI/20;
    widthIncreaseOnFire = PI/14;
    widthIncreaseOnHit = PI/10;
    
    widthDecreasePerSec = PI/20;
    
    maxDashSpeedBonus = 3;
    dashTime = 0.3;
    dashTimer = 0;
    
    shootEffectTime = 0.2;
    
    isDead = false;
    
}

void Player::update(float deltaTime, float deathAngle1, float deathAngle2){
    
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
    shootEffectTimer -= deltaTime;
    
    //is this fool dead?
    isDead = checkIfAngleIsInside(deathAngle1) || checkIfAngleIsInside(deathAngle2);
    
}

void Player::draw(){
    
    ofSetColor(color);
    if (isDead){
        ofSetColor(140, 50, 10);
    }
    ofFill();
    
    drawPaddle();
    
    ofNoFill();
    ofSetColor(230);
    drawPaddle();
    
}

void Player::drawPaddle(){
    float startAngle = curAngle - curWidth/2;
    float endAngle = curAngle + curWidth/2;
    
    //float angleStep = PI/32;
    
    int numPoints = curWidth * 30;// curWidth/angleStep;
    numPoints = MAX(numPoints, 2);
    //cout<<"numPoints "<<numPoints<<endl;
    
    ofBeginShape();
    
//    shootEffectTime = 0.5;
//    shootEffectTimer = shootEffectTime;
    int shootEffectRange = 0;
    int maxShootEffectRange = 6;
    float shootEffectMaxOffset = ofMap(shootEffectTimer, shootEffectTime, 0, 20, 0, true);
    if (shootEffectTimer > 0){
        shootEffectRange = ofMap(shootEffectTimer, shootEffectTime, 0, maxShootEffectRange, 1);
    }
    int shootEffectStart = (numPoints/2)-shootEffectRange;
    int shootEffectEnd = (numPoints/2)+shootEffectRange;
    
    //outter layer
    for  (int i=0; i<numPoints; i++){
        float thisAngle = ofMap(i, 0, numPoints-1, startAngle, endAngle);
        
        float shootEffectOffset = 0;
        if (shootEffectTimer > 0){
            shootEffectOffset = ofMap(shootEffectTimer, shootEffectTime, 0, 10, 0, true);
        }
        if (i>=shootEffectStart && i <=shootEffectEnd){
            shootEffectOffset += ofMap( abs(i-(numPoints/2)), 0, maxShootEffectRange, shootEffectMaxOffset, 0);
        }
        
        float thisX = cos(thisAngle) * (distFromCenter+height/2+shootEffectOffset);
        float thisY = sin(thisAngle) * (distFromCenter+height/2+shootEffectOffset);
        ofVertex(thisX, thisY);
        //ofDrawCircle(thisX, thisY, 2);
    }
    
    //inner layer
    for  (int i=numPoints-1; i>=0; i--){
        float thisAngle = ofMap(i, 0, numPoints-1, startAngle, endAngle);
        
        float shootEffectOffset = 0;
        if (shootEffectTimer > 0){
            shootEffectOffset = ofMap(shootEffectTimer, shootEffectTime, 0, 10, 0, true);
        }
        
        
        float thisX = cos(thisAngle) * (distFromCenter-height/2+shootEffectOffset);
        float thisY = sin(thisAngle) * (distFromCenter-height/2+shootEffectOffset);
        ofVertex(thisX, thisY);
        //ofDrawCircle(thisX, thisY, 2);
    }
    
    ofEndShape(true);
}

void Player::buttonPress(){
    curDir *= -1;
    targetWidth += widthIncreaseOnFire;
    dashTimer = dashTime;
    shootEffectTimer = shootEffectTime;
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
