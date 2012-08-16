//
//  ofxSubtitles.h
//  
//
//  Created by Andrew Bueno on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  @the Studio for Creative Inquiry



#pragma once

#include "ofMain.h"
#include "ofxTimecode.h"
#include "ofxSubtitleUnit.h"

//uncomment this to use FTGL for font rendering, which allos for Unicode such as Japanese
#define USE_FTGL

#ifdef USE_FTGL
#include "ofxFTGLFont.h"
#endif

class ofxSubtitles {

  public:
    ofxSubtitles();
    ~ofxSubtitles();
    
    void setup(string fontPath, int fontSize = 12, int fps = 30, ofxSubtitleJustification j =  TEXT_JUSTIFICATION_CENTER);
    void setup(string subPath, string fontPath, int fontSize = 12, int fps = 30, ofxSubtitleJustification j =  TEXT_JUSTIFICATION_CENTER);
    void loadFont(string path, int fontsize);
    
    bool load(string path); //Constructs subtitle vector
    bool save();  //saves any changes to the same file that was load
    bool save(string path); //saves changes to a new file, does not affect filePath
    
    vector<ofxSubtitleUnit>& getSubtitles();
    
    ofxSubtitleUnit* addSubtitle(long startTime, long endTime, string titleLine1, string titleLine2);
    
    void setJustification(ofxSubtitleJustification j);
    void setFramesPerSecond(int fps); //Timecode's default fps is 30
    void setFadeInterval(long milliseconds);
    
    //returns true if there are titles for this moment
    bool setTimeInMillseconds(long milliseconds);
    bool setTimeInSeconds(float seconds);
    bool setTimeInFrames(int frames);

    long getDurationInMillis();
    float getDurationInSeconds();
    
    //will return true once the very first time after a new title has been st
    bool isTitleNew();

    string getFilepath();
    
    //Creates a basic, non-bolded/italicized/underlined subtitle
    //void insertSubtitle(string startTime, string endTime, ofUTF8String subtitleText);
    //Allows you control over bolding, italics, and underlines
    //void insertSubtitle(string startTime, string endTime, ofUTF8String subtitleText, bool bold, bool ital, bool underl);
    //void removeSubtitle(int subtitleNumber); 
    void draw(float x, float y);
    void draw(ofPoint point);
    
	#ifdef USE_FTGL
    ofxFTGLFont font;
	#else
    ofTrueTypeFont font;
	#endif
    
  protected:
    string filepath;
    bool subsLoaded;
    long fadeTime; //In milliseconds
    long currentTime; //In milliseconds
    bool newTitle;
    
    ofBuffer srtFile;
    vector<ofxSubtitleUnit> subtitleList;    
    ofxSubtitleJustification subsJustification;
    ofxSubtitleUnit *currentlyDisplayedSub;
    
    ofRectangle textBounds;
    
    ofxTimecode timecode;

    ofxSubtitleUnit* searchSubtitleList(int minIndex, int maxIndex, long elapsedTime);
};

