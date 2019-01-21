/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:    MIT
 */


#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include <vector>
#include <sstream>

class ofApp: public ofBaseApp
{
public:
    //declare app functions
    void setup();
    void draw();
	void mousePressed(int x, int y, int button);
    void onStatus(const ofxTwitter::Status& status);
    void onError(const ofxTwitter::Error& error);
    void onException(const std::exception& exception);
	void onMessage(const ofJson& json);

	ofImage twitLogo;
	ofRectangle btn1, btn2, btn3, btn4;
    
	//declare twitter search client
    ofxTwitter::SearchClient client;
    
    //declare variables
	string wrapString(string text, int width); //string wrapping function
	ofTrueTypeFont myFont; //font object
	string text; //string to hold text once wrapped
	
    int count = 0;
    int countMissed = 0;
	stringstream tweets;

};