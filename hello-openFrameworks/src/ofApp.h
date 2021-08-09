#pragma once

#include "demoParticle.h"
#include "ofMain.h"
#include "ofxNetwork.h"
#include "wrapper_hand_tracking.pb.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void resetParticles();

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

    ofxUDPManager udpConnection;

    ::mediapipe::WrapperHandTracking *wrapper;
    vector<ofPoint> hand_landmarks;

    particleMode currentMode;
    string currentModeStr;

    vector<demoParticle> particles;
    vector<ofPoint> attractPoints;
    vector<ofPoint> attractPointsWithMovement;
};
