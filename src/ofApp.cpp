#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(10);
    
    arenaSize = 300;
    
    deathAngle1 = 0;
    
    for (int i=0; i<NUM_PLAYERS; i++){
        players[i].setup(i, arenaSize);
    }

    prevFrameTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    
    //have it always go slightly in one direction
    float noiseVal = ofMap(ofNoise(ofGetElapsedTimef()*0.2), 0, 1, -0.95, 1);
    deathAngle1 += PI*0.05 * deltaTime * noiseVal ;
    if (deathAngle1 > TWO_PI){
        deathAngle1 -= TWO_PI;
    }
    if (deathAngle1 < 0){
        deathAngle1 += TWO_PI;
    }
    deathAngle2 = deathAngle1 + PI;
    if (deathAngle2 > TWO_PI){
        deathAngle2 -= TWO_PI;
    }
    if (deathAngle2 < 0){
        deathAngle2 += TWO_PI;
    }
    
    //update players
    for (int i=0; i<NUM_PLAYERS; i++){
        players[i].update(deltaTime, deathAngle1, deathAngle2);
        //what the fuck? why does this cout prevent a bug where blue player is marked as dead if green is dead?
        //cout<<"wut"<<endl;
        //cout<<"player "<<i<<" "<<players[i].isDead<<endl;
    }
    
    //update bullets
    for (int i=bullets.size()-1; i>=0; i--){
        bullets[i].update(deltaTime, arenaSize);
        
        //check if anybody could be getting hit
        if (!bullets[i].outOfBounds){
            float distFromCenter = ofDist(0,0, bullets[i].pos.x, bullets[i].pos.y);
            if (distFromCenter > players[0].distFromCenter-players[0].height-bullets[i].size){
                float angle = atan2(bullets[i].pos.y, bullets[i].pos.x);
                for (int p=0; p<NUM_PLAYERS; p++){
                    if (&players[p] != bullets[i].parent){
                        if(players[p].checkIfAngleIsInside(angle)){
                            players[p].getHit();
                            bullets[i].killMe = true;
                        }
                    }
                }
            }
        }
        
        //check if we should kill the bullet
        if (bullets[i].killMe){
            bullets.erase(bullets.begin()+i);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(arenaSize+100, arenaSize+100);
    
    float arenaSpinAngle = -ofGetElapsedTimef() * 0.05;
    
    //the death line
    float deathDist = arenaSize + 80;
    float deathInnerDist = 80;
    ofSetColor(230);
    
    ofDrawLine(cos(deathAngle1)*deathDist, sin(deathAngle1)*deathDist, cos(deathAngle2)*deathDist, sin(deathAngle2)*deathDist);
    drawHashCircle(0, 0, deathInnerDist, 57, 3, -arenaSpinAngle);
    
    ofNoFill();
    
    //the arena
    drawHashCircle(0, 0, arenaSize, 102, 3, arenaSpinAngle);
    //int numDots = 102;
    
    
    //the bullets
    for (int i=0; i<bullets.size(); i++){
        bullets[i].draw();
    }
    
    //the players
    for (int i=0; i<NUM_PLAYERS; i++){
        players[i].draw();
    }
    
    
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawHashCircle(float x, float y, float size, int numDots, int spacing, float baseAngle){
    
    float angleSpacing = TWO_PI / (float)numDots;
    for (int i=0; i<numDots; i+=spacing){
        float angle1 = baseAngle + angleSpacing * i;
        float angle2 = baseAngle + angleSpacing * (i+1);
        float x1 = cos(angle1) * size;
        float y1 = sin(angle1) * size;
        float x2 = cos(angle2) * size;
        float y2 = sin(angle2) * size;
        ofDrawLine(x1, y1, x2, y2);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'q'){
        fire(&players[0]);
    }
    if (key == 'p'){
        fire(&players[1]);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::fire(Player * player){
    player->buttonPress();
    
    //account for the dash
    float angleOffset = PI/16 * player->curDir;
    
    Bullet bul;
    float x = cos(player->curAngle + angleOffset) * player->distFromCenter;
    float y = sin(player->curAngle + angleOffset) * player->distFromCenter;
    bul.setup(x, y, player->curAngle+PI+angleOffset, player);
    bullets.push_back(bul);
}
