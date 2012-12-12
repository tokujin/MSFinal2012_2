#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(false);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    // you can alternatively create a 'base' user class
    //    ofxOpenNIUser user;
    //    user.setUseMaskTexture(true);
    //    user.setUsePointCloud(true);
    //    user.setPointCloudDrawSize(2);
    //    user.setPointCloudResolution(2);
    //    openNIDevice.setBaseUserClass(user);
    
    //load image
    image.loadImage("fencing.png");
    sound.loadSound("sounds/orgolM.wav");
    verdana.loadFont(ofToDataPath("verdana.ttf"), 12);
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
    
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
//    ofSetColor(ofRandom(220,240));
    
    ofSetColor(ofRandom(240,255), 139, 212);
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
       

        /*give up draw Mask
        if (numUsers==2 && (counter2 - counter) < -1) {
            user.drawMask();
        }
            counter2 = counter;
        
        if(user.isSkeleton()){
            counter = counter +1;
        };*/

        //extract heart
        xh = ((user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition().x)+(user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition().x))*0.5;
        yh =  ((user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition().y)+(user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition().y))*0.5;
        
        
        //extract joint position left
        x0 = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition().x;
        y0 = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition().y;
        x1 = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition().x;
        y1 = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition().y;
        
        
        l1 = ofDist(x0,y0,x1,y1);
        theta1 = acos((x1-x0)/l1);
        angle1 = 180 * theta1;
        c1 = cos(theta1);
        s1 = sin(theta1);
        c2 = cos(2*PI - theta1);
        s2 = sin(2*PI - theta1);
        
        d1 = ofDist(xe,ye,xh,yh);
        
        //x-coordinate, y-coordinate, tip of sword
        if (y0<y1) {
            xe = x1 + l1 * c1 * 2.5;
            ye = y1 + l1 * s1 * 2.5;
            xe1 = x1 + l1 * c1 * 2.2;
            ye1 = x1 + l1 * s1 * 2.2;
        }else{
            xe = x1 + l1 * c2 * 2.5;
            ye = y1 + l1 * s2 * 2.5;
            xe1 = x1 + l1 * c2 * 2.2;
            ye1 = x1 + l1 * s2 * 2.2;
        }
        
        p = l1/100;        
        
        ofSetColor(255, 139, 212);
        ofPushMatrix();
        ofTranslate(x1,y1);
        ofSetLineWidth(3);
        if(y0<y1){
            if(d1<50){
                sound.play();
                ofCircle(xh-x1,yh-y1,30);
                if(xh<320){
                    scoreR = scoreR +20;
                }else{scoreL = scoreL + 20;}
            }else{}
            ofLine(0, 0,xe-x1,ye-y1);

            ofPushMatrix();
            ofRotate(angle1/2+90);
            ofBeginShape();
            ofBezier(0, -32*p, -24*p, -24*p, -24*p, 24*p, 0, 32*p);
            ofEndShape();
            ofPopMatrix();
        }
        else{
            if(d1<50){
                ofCircle(xh-x1,yh-y1,30);
                sound.play();
                if(xh<320){
                    scoreR = scoreR +20;
                }else{scoreL = scoreL + 20;}
            }else{}
            
            ofLine(0, 0,xe-x1,ye-y1);

            ofPushMatrix();
            ofRotate(-angle1/2+270);
            ofBeginShape();
            ofBezier(0 , -32*p, -24*p, -24*p, -24*p, 24*p, 0, 32*p);
            ofEndShape();
            ofPopMatrix();
            
            
        }
        ofPopMatrix();
        
        
        
        
        //        }
        // you can also access the pixel and texture references individually:
        
        // TEXTURE REFERENCE
        //ofTexture & tex = user.getMaskTextureReference();
        // do something with texture...
        
        // PIXEL REFERENCE
        //ofPixels & pix = user.getMaskPixels();
        // do something with the pixels...
        
        // and point clouds:
        
        ofPushMatrix();
        // move it a bit more central
        //ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        
        // you can also access the mesh:
        
        // MESH REFERENCE
        //ofMesh & mesh = user.getPointCloud();
        // do something with the point cloud mesh
        
        ofPopMatrix();
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
	
    ofSetColor(240, 0, 0);
	string msg = " scoreL: " + ofToString(scoreL) + " scoreR: " + ofToString(scoreR);
    
	verdana.drawString(msg, 170, openNIDevice.getNumDevices() * 80 - 20);
    
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}