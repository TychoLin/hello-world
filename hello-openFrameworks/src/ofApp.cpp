#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetVerticalSync(true);

    ofxUDPSettings settings;
    settings.receiveOn(8080);
    settings.blocking = false;

    udpConnection.Setup(settings);

    wrapper = new ::mediapipe::WrapperHandTracking();
    wrapper->InitAsDefaultInstance();

    hand_landmarks.assign(21, ofPoint(-ofGetWidth(), -ofGetHeight()));

    int num = 1000;
    particles.assign(num, demoParticle());
    currentMode = PARTICLE_MODE_NEAREST_POINTS_REPEL;

    currentModeStr = "5 - PARTICLE_MODE_NEAREST_POINTS_REPEL: repels from hand";

    resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{
    // these are the attraction points used in the forth demo
    attractPoints.clear();
    attractPoints = hand_landmarks;

    attractPointsWithMovement = attractPoints;

    for (unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].setMode(currentMode);
        particles[i].setAttractPoints(&attractPointsWithMovement);
        particles[i].reset();
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    char udpMessage[100000];
    auto ret = udpConnection.Receive(udpMessage, 100000);
    if (ret > 0)
    {
        wrapper->Clear();
        wrapper->ParseFromArray(udpMessage, udpConnection.GetReceiveBufferSize());

        for (int i = 0; i < wrapper->landmarks().landmark_size(); i++)
        {
            auto &landmark = wrapper->landmarks().landmark(i);
            hand_landmarks[i] = ofPoint(ofMap(landmark.x(), 0, 1, 0, ofGetWidth()), ofMap(landmark.y(), 0, 1, 0, ofGetHeight()));
        }
    }

    if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
    {
        attractPointsWithMovement = vector<ofPoint>{hand_landmarks.at(8)};
    }
    else if (currentMode == PARTICLE_MODE_NEAREST_POINTS_REPEL)
    {
        attractPointsWithMovement = hand_landmarks;
    }

    for (unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].setMode(currentMode);
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient(ofColor(60, 60, 60), ofColor(10, 10, 10));

    ofPushStyle();
    ofFill();
    for (size_t i = 0; i < hand_landmarks.size(); i++)
    {
        ofSetColor(ofColor::black);
        ofDrawBitmapString(ofToString(i), hand_landmarks[i].x + 10, hand_landmarks[i].y + 10);
        ofSetColor(ofColor::cyan, 120);
        ofDrawEllipse(hand_landmarks[i].x, hand_landmarks[i].y, 15, 15);
    }
    ofSetColor(ofColor::magenta, 120);
    ofSetLineWidth(3);
    ofDrawLine(hand_landmarks[0], hand_landmarks[1]);
    ofDrawLine(hand_landmarks[0], hand_landmarks[5]);
    ofDrawLine(hand_landmarks[0], hand_landmarks[17]);
    for (int i = 5; i < 17; i += 4)
        ofDrawLine(hand_landmarks[i], hand_landmarks[i + 4]);
    for (int i = 1; i <= 17; i += 4)
        for (int ii = i; ii < i + 3; ii++)
            ofDrawLine(hand_landmarks[ii], hand_landmarks[ii + 1]);
    ofPopStyle();

    for (unsigned int i = 0; i < particles.size(); i++)
    {
        particles[i].draw();
    }

    ofSetColor(230);
    ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == '1')
    {
        currentMode = PARTICLE_MODE_ATTRACT;
        currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    }
    if (key == '2')
    {
        currentMode = PARTICLE_MODE_REPEL;
        currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
    }
    if (key == '3')
    {
        currentMode = PARTICLE_MODE_NEAREST_POINTS;
        currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
    }
    if (key == '4')
    {
        currentMode = PARTICLE_MODE_NOISE;
        currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
        resetParticles();
    }
    if (key == '5')
    {
        currentMode = PARTICLE_MODE_NEAREST_POINTS_REPEL;
        currentModeStr = "5 - PARTICLE_MODE_NEAREST_POINTS_REPEL: repels from hand";
        resetParticles();
    }

    if (key == ' ')
    {
        resetParticles();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
