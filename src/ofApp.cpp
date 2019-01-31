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

	//this will load the image of the twitter logo
	twitLogo.load("twitterLogo.png");

	//this will initialize the size and position of all 10 buttons
	btn1.set(90, 50, 75, 50);
	btn2.set(190, 50, 75, 50);
	btn3.set(290, 50, 75, 50);
	btn4.set(390, 50, 75, 50);
	btn5.set(90, 120, 75, 50);
	btn6.set(190, 120, 75, 50);
	btn7.set(290, 120, 75, 50);
	btn8.set(390, 120, 75, 50);
	btn9.set(490, 50, 75, 50);
	btn10.set(490, 120, 75, 50);

	myFont.load("font.ttf", 10, true, true); //load font
	myFont.setLineHeight(20.0f); //set line height of font
}

void ofApp::draw()
{
	//
	text = wrapString(tweets.str(), 500);

	//This sets the colour of the background
	ofBackground(192, 222, 237);

	//This will draw the logo
	ofSetColor(255);
	twitLogo.draw(5, 5);

	//This will draw btn1
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn1);
	ofSetColor(255);
	myFont.drawString("22/01/2019", 91, 79);

	//This will draw btn2
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn2);
	ofSetColor(255);
	myFont.drawString("#thankful", 196, 79);

	//This will draw btn3
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn3);
	ofSetColor(255);
	myFont.drawString("Thomas", 301, 79);

	//This will draw btn4
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn4);
	ofSetColor(255);
	myFont.drawString("BathSpa", 401, 79);

	//This will draw btn5
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn5);
	ofSetColor(255);
	myFont.drawString("Trump", 109, 149);

	//This will draw btn6
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn6);
	ofSetColor(255);
	myFont.drawString("YuGiOh", 206, 149);

	//This will draw btn7
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn7);
	ofSetColor(255);
	myFont.drawString("ofxTwitter", 293, 149);

	//This will draw btn8
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn8);
	ofSetColor(255);
	myFont.drawString("Unity", 411, 149);

	//This will draw btn9
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn9);
	ofSetColor(255);
	myFont.drawString("Sonic", 511, 79);

	//This will draw btn10
	ofSetColor(100, 149, 237);
	ofDrawRectangle(btn10);
	ofSetColor(255);
	myFont.drawString("Avengers", 499, 149);

    //counts number of tweets
    int total = count + countMissed;

	ofSetColor(0, 0, 0);
	myFont.drawString(text, 75, 180); //draw text to screen

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
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of 22/01/2019
	if (btn1.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 1" << std::endl;
		tweets.str("");
		client.search("22/01/2019");
	}
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of #thankful
	if (btn2.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 2" << std::endl;
		tweets.str("");
		client.search("#thankful");
	}
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of Thomas
	if (btn3.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 3" << std::endl;
		tweets.str("");
		client.search("Thomas");
	}
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of BathSpa
	if (btn4.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 4" << std::endl;
		tweets.str("");
		client.search("BathSpa");
	}
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of Trump
	if (btn5.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 5" << std::endl;
		tweets.str("");
		client.search("Trump");
	}
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of YuGiOh
	if (btn6.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 6" << std::endl;
		tweets.str("");
		client.search("YuGiOh");
	}
	//If btn7 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of ofxTwitter
	if (btn7.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 7" << std::endl;
		tweets.str("");
		client.search("ofx Twitter");
	}
	//If btn8 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of Unity
	if (btn8.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 8" << std::endl;
		tweets.str("");
		client.search("Unity");
	}
	//If btn9 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of Sonic
	if (btn9.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 9" << std::endl;
		tweets.str("");
		client.search("Sonic");
	}
	//If btn10 is pressed it will clear all tweets currently being displayed and replace them with all tweets with the topic of Avengers
	if (btn10.inside(x, y)) {
		client.stop();
		std::cout << "Clicked button 10" << std::endl;
		tweets.str("");
		client.search("Avengers");
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