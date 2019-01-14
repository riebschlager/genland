#include "ofApp.h"

void ofApp::setup()
{
  ofSetFrameRate(60);
  ofBackground(0);
  mCanvas.allocate(CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGBA);
  mCanvas.begin();
  ofClear(0, 0, 0, 0);
  mCanvas.end();
  mIsGuiVisible = true;
  mGui.setup();

  mGui.add(mNoiseScale.setup("Noise Scale",
                             ofVec3f(0.0001f, 0.0001f, 0.0001f),
                             ofVec3f(0.0000f, 0.0000f, 0.0000f),
                             ofVec3f(0.001f, 0.001f, 0.01f)));

  mGui.add(mTravel.setup("Travel",
                         ofVec2f(-500, 500),
                         ofVec2f(-CANVAS_HEIGHT, -CANVAS_HEIGHT),
                         ofVec2f(CANVAS_HEIGHT, CANVAS_HEIGHT)));

  mGui.add(mScale.setup("Scale", ofVec2f(0, 1), ofVec2f(0, 0), ofVec2f(3, 3)));

  mBasePath = ofFilePath::getUserHomeDir() + "/Documents/Art/";

  loadSlices("powder", 1200, 1200);
  loadSlices("powder-shadow", 1200, 1200);
  // loadSlices("watercolor", 1200, 1200);
  loadSlices("blood", 1200, 1200);
  loadSlices("line", 1200, 1200);
  // loadSlices("painter", 1200, 1200);
  loadSources("drk");
}

void ofApp::render()
{
  mCanvas.begin();
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  int x = ofRandom(CANVAS_WIDTH);
  float noise = ofMap(ofNoise(x * mNoiseScale->x, mY * mNoiseScale->y, ofGetFrameNum() * mNoiseScale->z), 0, 1, mTravel->x, mTravel->y);
  int sliceIndex = floor(ofRandom(mSlices.size() - 1));

  ofPushMatrix();
  ofTranslate(x, mY + noise);
  ofColor color = mSources[0].getColor(x, ofClamp(mY + noise, 0, CANVAS_HEIGHT - 1));
  ofSetColor(color, ofRandom(255));
  ofScale(ofRandom(mScale->x, mScale->y));
  ofImage *img = &mSlices[sliceIndex];
  img->draw(-img->getWidth() / 2, -img->getHeight() / 2);
  ofPopMatrix();
  mCanvas.end();
}

void ofApp::update()
{
  if (mIsDrawing)
  {
    for (int i = 0; i < 100; i++)
    {
      render();
    }
  }
}

void ofApp::draw()
{
  mCanvas.draw(0, 0, APP_WIDTH, APP_HEIGHT);
  if (mIsGuiVisible)
  {
    mGui.draw();
  }
}

void ofApp::saveFbo()
{
  ofFbo img;
  ofPixels pixels;
  img.allocate(CANVAS_WIDTH, CANVAS_HEIGHT, GL_RGBA);
  img.begin();
  ofBackground(0);
  mCanvas.draw(0, 0);
  img.end();
  img.readToPixels(pixels);
  ofSaveImage(pixels, "output/image" + ofToString(ofGetUnixTime()) + ".tif");
}

void ofApp::keyPressed(int key)
{
  if (key == 'c')
  {
    mCanvas.begin();
    ofClear(0, 0, 0, 0);
    mCanvas.end();
  }
  if (key == 's')
  {
    saveFbo();
  }
}

void ofApp::keyReleased(int key)
{
}

void ofApp::mouseMoved(int x, int y)
{
  mY = ofMap(y, 0, APP_HEIGHT, 0, CANVAS_HEIGHT, true);
}

void ofApp::mouseDragged(int x, int y, int button)
{
  mY = ofMap(y, 0, APP_HEIGHT, 0, CANVAS_HEIGHT, true);
}

void ofApp::mousePressed(int x, int y, int button)
{
  mIsDrawing = true;
  mY = ofMap(y, 0, APP_HEIGHT, 0, CANVAS_HEIGHT, true);
}

void ofApp::mouseReleased(int x, int y, int button)
{
  mIsDrawing = false;
}

void ofApp::mouseEntered(int x, int y)
{
}

void ofApp::mouseExited(int x, int y)
{
}

void ofApp::windowResized(int w, int h)
{
}

void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
