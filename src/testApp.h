#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"

class testApp : public ofBaseApp{
private:
    ofImage image;
    
public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    float theta1,theta2;
    float x0,y0,x1,y1,x2,y2,x3,y3,xe,ye,xe1,ye1,xh,yh,oldX, oldY, V=0;
    float d1,d2;
    float vx=0,vy;
    float c1,s1,c2,s2,c3,s3,c4,s4;
    float l1,l2;
    float angle1,angle2;
    float p; //adjustment of the size of the sword
    int counter=0, counter2 =0;
    int scoreL, scoreR, velo;
    
    ofTrueTypeFont verdana;
    ofSoundPlayer sound1, sound2;
    
};

#endif