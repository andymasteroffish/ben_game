#pragma once

#include "ofMain.h"
#include "Player.hpp"
#include "Bullet.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void fire(Player * player);
    
    float prevFrameTime;
    float deltaTime;
    
    
    float arenaSize;
    
    float deathAngle;
    
#define NUM_PLAYERS 2
    Player players[NUM_PLAYERS];
    vector<Bullet> bullets;
    
    
};
