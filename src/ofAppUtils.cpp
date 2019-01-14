#include "ofApp.h"

ofVec2f ofApp::resizeProportionally(float srcWidth, float srcHeight, float maxWidth, float maxHeight)
{
    float ratio = min(maxWidth / srcWidth, maxHeight / srcHeight);
    return ofVec2f(srcWidth * ratio, srcHeight * ratio);
}

void ofApp::loadSlices(string folderName)
{
    string path = mBasePath + "slices/" + folderName;
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        ofImage img;
        img.load(dir.getPath(i));
        mSlices.push_back(img);
    }
}

void ofApp::loadSlices(string folderName, int maxWidth, int maxHeight)
{
    string path = mBasePath + "slices/" + folderName;
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        ofImage img;
        img.load(dir.getPath(i));
        ofVec2f r = resizeProportionally(img.getWidth(), img.getHeight(), maxWidth, maxHeight);
        img.resize(r.x, r.y);
        mSlices.push_back(img);
    }
}

void ofApp::loadSlicesFromSource(string folderName, int numberOfSlices, int maxWidth, int maxHeight)
{
    string path = mBasePath + "sources/" + folderName;
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        ofImage img;
        img.load(dir.getPath(i));
        for (int j = 0; j < numberOfSlices; j++)
        {
            ofImage slice;
            int w = ofRandom(maxWidth);
            int h = ofRandom(maxHeight);
            int x = ofRandom(0, img.getWidth() - w);
            int y = ofRandom(0, img.getHeight() - h);
            slice.cropFrom(img, x, y, w, h);
            mSlices.push_back(slice);
        }
    }
}

void ofApp::loadSources(string folderName)
{
    string path = mBasePath + "sources/" + folderName;
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        ofImage img;
        img.load(dir.getPath(i));
        img.resize(CANVAS_WIDTH, CANVAS_HEIGHT);
        mSources.push_back(img);
    }
}
