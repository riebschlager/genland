#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define APP_WIDTH 1272
#define APP_HEIGHT 1080
#define CANVAS_WIDTH 7632
#define CANVAS_HEIGHT 6480

class ofApp : public ofBaseApp
{

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
	void render();

	void loadSlices(string folderName, int maxWidth, int maxHeight);
	void loadSlices(string folderName);
	void loadSlicesFromSource(string folderName, int numberOfSlices, int maxWidth, int maxHeight);
	void loadSources(string folderName);
	void saveFbo();

	ofFbo mCanvas;
	string mBasePath;
	vector<ofImage> mSlices;
	vector<ofImage> mSources;
	ofVec2f resizeProportionally(float srcWidth, float srcHeight, float maxWidth, float maxHeight);
	bool mIsDrawing;
	int mY;
	bool mIsGuiVisible;
	ofxPanel mGui;
	ofxVec3Slider mNoiseScale;
	ofxVec2Slider mTravel;
	ofxVec2Slider mScale;
};
