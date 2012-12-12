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
    
    int i,j;
    
	ofxOpenNI openNIDevice;
    float theta1,theta2;
    float xle,yle,xlh,ylh,xre,yre,xrh,yrh,xtor,ytor;
    float xlt[4],ylt[4],xrt[4],yrt[4];
    float dl1,dl2,dl3,dl4,dl5,dl6,dl7,dr1,dr2,dr3,dr4,dr5,dr6,dr7;
    float cl1,sl1,cl2,sl2,cr1,sr1,cr2,sr2;
    float l1,l2;
    float angle1,angle2;
    float pl,pr; //adjustment of the size of the sword
    float theta[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    
    ofTrueTypeFont verdana;
    ofSoundPlayer sound;
    
};

#endif