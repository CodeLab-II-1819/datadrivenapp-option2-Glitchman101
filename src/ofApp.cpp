/*
 Starter code for Data Driven App assignment CodeLab II
 Based on basic example of ofxTwitter by Christopher Baker
 <https://christopherbaker.net>
 SPDX-License-Identifier:	MIT
*/


#include "ofApp.h"

//initial app setup
void ofApp::setup()
{
	twitLogo.load("twitterLogo.png");

	btn1.set(150, 100, 50, 50);
	btn2.set(250, 100, 50, 50);
	btn3.set(350, 100, 50, 50);
	btn4.set(150, 200, 50, 50);


	myFont.load("font.ttf", 10, true, true); //load font
	myFont.setLineHeight(20.0f); //set line height of font

    //lower app frameRate
    ofSetFrameRate(30);

    // Easily register for all search events.
    client.registerSearchEvents(this);

    /* Ensure you have created and app and updated the credentials file
     in the bin/data folder. You can create app at:
     https://apps.twitter.com */
    //Load in the credentials for access to twitter
    client.setCredentialsFromFile("credentials.json");

    /* Sets the polling interval for 6 seconds. This means new tweets
    are retrived every 6 seconds*/
    client.setPollingInterval(6000);

    // This starts a simple search for an emoticon.
    client.search(":)");
    // Tweets are retured in the callbacks onStatus(..), onError(...), etc.
	
    /*
     To design more complex searches, see thesearch the API documentation here:
     https://dev.twitter.com/rest/public/
     and:
     https://developer.twitter.com/en/docs/tweets/rules-and-filtering/overview/standard-operators
     You can then use the search object ofxTwitter::SearchQuery like this:
     
        ofxTwitter::SearchQuery query(":)");
        query.setLanguage("en");
        client.search(query);

     This would return only tweets in English
    
     To see how else you can refine the queries you should explore
     the .h files included in:
     openFrameworks/addons/ofxTwitter/libs/ofxTwitter/include/ofx/Twitter
     In particular search.h
    */
}

void ofApp::draw()
{
	text = wrapString(tweets.str(), 300);

	ofBackground(192, 222, 237);

	ofSetColor(255);
	twitLogo.draw(5, 5);

	ofSetColor(255, 0, 255);
	ofDrawRectangle(btn1);

	ofSetColor(255, 0, 0);
	ofDrawRectangle(btn2);

	ofSetColor(255, 255, 0);
	ofDrawRectangle(btn3);

	ofSetColor(0, 255, 0);
	ofDrawRectangle(btn4);

	

    //counts number of tweets
    int total = count + countMissed;

	ofSetColor(0, 0, 0);
	myFont.drawString(text, 100, 210); //draw text to screen

    //string stream used to display number of tweets recived
    /*std::stringstream ss;
    ss << "  Received: " << count << std::endl;
    ss << "    Missed: " << countMissed << std::endl;
    ss << "     Total: " << total << std::endl;*/
	ofSetColor(0, 0, 0);
   //ofDrawBitmapString(tweets.str(), 10, 10);
	
}

//This function is called everytime the a new tweet is recieved
void ofApp::onStatus(const ofxTwitter::Status& status)
{
    //increase tweet count
    count++;
    
    //output the tweet author and text
    tweets << "User: " << status.user()->name() << endl;
    tweets << "Tweet: " << status.text() << endl;
    tweets << "\n -----------------------------\n" << endl;
	client.stop();
}

//returns an error message if error encountered recieving tweets
void ofApp::onError(const ofxTwitter::Error& error)
{
    std::cout << "Error: " << error.code() << " " << error.message();
}

//returns an exception message if exception encountered recieving tweets
void ofApp::onException(const std::exception& notice)
{
    std::cout << "Exception: " << notice.what();
}

void ofApp::onMessage(const ofJson& json)
{
	// This is the raw message json and is ignored here.
}

void ofApp::mousePressed(int x, int y, int button) {
	if (btn1.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 1" << std::endl;
		tweets.str("");
		client.search("Code");
	}
	if (btn2.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 2" << std::endl;
		tweets.str("");
		client.search("#thankful");
	}
	if (btn3.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 3" << std::endl;
		tweets.str("");
		client.search("Thomas");
	}
	if (btn4.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 4" << std::endl;
		tweets.str("");
		client.search("BathSpa");
	}


}
string ofApp::wrapString(string text, int width) {
	string typeWrapped = "";
	string tempString = "";
	vector <string> words = ofSplitString(text, " "); //create vector full of individual words in string passed in

	for (int i = 0; i<words.size(); i++) { //run through vector
		string wrd = words[i]; //get current word in vector

							   // if we aren't on the first word, add a space
		if (i > 0) {
			tempString += " ";
		}
		tempString += wrd; //add current word to temp string

		int stringwidth = myFont.stringWidth(tempString); //set string width to length of line

		if (stringwidth >= width) {//check string with to add either space or new line before current word
			typeWrapped += "\n"; //if line is now longer than desired width add a new line
			tempString = wrd; // make sure we're including the extra word on the next line
		}
		else if (i > 0) {
			typeWrapped += " "; // if we aren't on the first word, add a space
		}
		typeWrapped += wrd; //add current word to string to be returned with new lines for wrapping
	}

	return typeWrapped;

}