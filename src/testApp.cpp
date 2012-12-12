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
    //    openNIDevice.setMaxNumUsers(8);
    openNIDevice.start();
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(false); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(1); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    // 　　you can alternatively create a 'base' user class
    //    ofxOpenNIUser user;
    //    user.setUseMaskTexture(true);
    //    user.setUsePointCloud(true);
    //    user.setPointCloudDrawSize(2);
    //    user.setPointCloudResolution(2);
    //    openNIDevice.setBaseUserClass(user);
    
    //    load image
    image.loadImage("fencing.png");
    sound.loadSound("sounds/glass1.wav");
    verdana.loadFont(ofToDataPath("verdana.ttf"), 12);
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    
    //
    l1 = ofDist(xle,yle,xlh,ylh);
    theta1 = acos((xlh-xle)/l1);
    angle1 = 180 * theta1;
    cl1 = cos(theta1);
    sl1 = sin(theta1);
    cl2 = cos(2*PI - theta1);
    sl2 = sin(2*PI - theta1);
    
    l2 = ofDist(xre,yre,xrh,yrh);
    theta2 = acos((xrh-xre)/l1);
    angle2 = 180 * theta2;
    cr1 = cos(theta2);
    sr1 = sin(theta2);
    cr2 = cos(2*PI - theta2);
    sr2 = sin(2*PI - theta2);
    
    //x-coordinate, y-coordinate, tip of sword
    if (yle<ylh) {
        xlt[0] = xlh + l1 * cl1 * 3.2;
        ylt[0] = ylh + l1 * sl1 * 3.2;
        xlt[1] = xlh + l1 * cl1 * 2.4;
        ylt[1] = xlh + l1 * sl1 * 2.4;
        xlt[2] = xlh + l1 * cl1 * 1.6;
        ylt[2] = xlh + l1 * sl1 * 1.6;
        xlt[3] = xlh + l1 * cl1 * 0.8;
        ylt[3] = xlh + l1 * sl1 * 0.8;
        
        
    }else{
        xlt[0] = xle + l1 * cl2 * 3.2;
        ylt[0] = yle + l1 * sl2 * 3.2;
        xlt[1] = xlh + l1 * cl2 * 2.4;
        ylt[1] = xlh + l1 * sl2 * 2.4;
        xlt[2] = xlh + l1 * cl2 * 1.6;
        ylt[2] = xlh + l1 * sl2 * 1.6;
        xlt[3] = xlh + l1 * cl2 * 0.8;
        ylt[3] = xlh + l1 * sl2 * 0.8;
    }
    
    if (yre<yrh) {
        xrt[0] = xrh + l2 * cr1 * 3.2;
        yrt[0] = yrh + l2 * sr1 * 3.2;
        xlt[1] = xrh + l2 * cr1 * 2.4;
        ylt[1] = xrh + l2 * sr1 * 2.4;
        xlt[2] = xrh + l2 * cr1 * 1.6;
        ylt[2] = xrh + l2 * sr1 * 1.6;
        xlt[3] = xrh + l2 * cr1 * 0.8;
        ylt[3] = xrh + l2 * sr1 * 0.8;
    }else{
        xrt[0] = xrh + l2 * cr2 * 3.2;
        yrt[0] = yrh + l2 * sr2 * 3.2;
        xrt[1] = xrh + l2 * cr2 * 2.4;
        yrt[1] = xrh + l2 * sr2 * 2.4;
        xrt[2] = xrh + l2 * cr2 * 1.6;
        yrt[2] = xrh + l2 * sr2 * 1.6;
        xrt[3] = xrh + l2 * cr2 * 0.8;
        yrt[3] = xrh + l2 * sr2 * 0.8;
    }
    
    
    pl = l1/100;
    pr = l2/100;
    
    
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
    
    // iterate through users
    
    for (int i = 0; i < numUsers; i++){
        
        //get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        //extract joint position torso
        xtor = user.getJoint(JOINT_TORSO).getProjectivePosition().x;
        ytor = user.getJoint(JOINT_TORSO).getProjectivePosition().y;
        
        
        
        //extract joint position left
        xle = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition().x;
        yle = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition().y;
        xlh = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition().x;
        ylh = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition().y;
        
        //extract joint position right
        xre = user.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition().x;
        yre = user.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition().y;
        xrh = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition().x;
        yrh = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition().y;
        
        
        
        
        //sound effect collision detection
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if(ofDist(xlt[i],ylt[i],xrt[i],yrt[i]) < 30){
                    sound.play();
                    ofCircle(xlt[i],ylt[i],30);
                }else{};
            }
        }
        
        
        
        //        draw the mask texture for this user
        
        //        user.drawMask(); // 場面が暗くなって、マスクだけ表示されるようになるやつ
        //        if (user.isSkeleton()){
        //            ofxOpenNIJoint leftElbow = ; Patricioが教えてくれたやつ
        //            ofEllipse(user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition().x, user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition().y, 40, 40);
        
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255)); // color of sword
        ofSetLineWidth(6);
        
        //Start Drawing!!!
        //        if (xtor > 320) {
        //left hand
        ofPushMatrix();//LEVEL1
        ofTranslate(xlh,ylh);
        
        if(yle<ylh){ //when left elbow is below left hand
            ofLine(0, 0,xlt[0]-xlh,ylt[0]-ylh);
            
            ofPushMatrix();//LEVEL2-1
            ofRotate(angle1/2+90);
            ofEllipse(0,0,50*pl,20*pl);
            /*
             ofBeginShape();
             ofBezier(0, -32*pl, -24*pl, -24*pl, -24*pl, 24*pl, 0, 32*pl);
             ofEndShape();
             */
            ofPopMatrix();//LEVEL2-1
            
        }
        else{
            ofLine(0, 0,xlt[0]-xlh,ylt[0]-ylh);
            
            ofPushMatrix();//LEVEL2-2
            ofRotate(-angle1/2+270);
            ofEllipse(0,0,50*pl,20*pl);
            /*
             ofBeginShape();
             ofBezier(0 , -32*pl, -24*pl, -24*pl, -24*pl, 24*pl, 0, 32*pl);
             ofEndShape();
             */
            ofPopMatrix();//LEVEL2-2
        }
        ofPopMatrix();//LEVEL1
        
        
        //        }
        //        else{
        //            //right hand
        //            ofPushMatrix();//LEVEL1
        //            ofTranslate(xrh,yrh);
        //            ofSetLineWidth(6);
        //            if(yre<yrh){
        //
        //                ofLine(0, 0,xrt[0]-xrh,yrt[0]-yrh);
        //                ofPushMatrix();//LEVEL2-1
        //                ofRotate(angle2/2+90);
        //                ofBeginShape();
        //                ofBezier(0, -32*pr, 24*pr, -24*pr, 24*pr, 24*pr, 0, 32*pr);
        //                ofEndShape();
        //                ofPopMatrix();//LEVEL2-1
        //            }
        //            else{
        //
        //                ofLine(0, 0,xrt[0]-xrh,yrt[0]-yrh);
        //
        //                ofPushMatrix();//LEVEL2-2
        //                ofRotate(-angle2/2+270);
        //                ofBeginShape();
        //                ofBezier(0 , -32*pr, 24*pr, -24*pr, 24*pr, 24*pr, 0, 32*pr);
        //                ofEndShape();
        //                ofPopMatrix();//LEVEL2-2
        //            }
        //            ofPopMatrix();
        //
        //        }
        
        
        
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
    
    ofSetColor(0, 255, 0);
	string msg = " xlt: " + ofToString(xlt);
    
	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
    
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