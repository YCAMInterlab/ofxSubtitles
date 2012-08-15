//
//  ofxSubtitles.h
//  
//
//  Created by Andrew Bueno on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  @the Studio for Creative Inquiry

#ifndef _ofxSubtitles_h
#define _ofxSubtitles_h
#include <iostream>
#include "ofMain.h"
#include "ofxTimecode.h"
#include "ofUnicode.h"

#define MAX_LINES_PER_SUB_UNIT 2


enum textJustification { TEXT_JUSTIFICATION_LEFT, TEXT_JUSTIFICATION_CENTER, TEXT_JUSTIFICATION_RIGHT };


class SubtitleUnit{

public:
    
    //Set the index of the SubtitleUnit within a larger set of
    //SubtitleUnits
    void setIndex(int i);
    int getIndex();
    
    //Set and get start and end times
    void setStartTime(long millis);
    long getStartTime();    
    
    void setEndTime(long millis);
    long getEndTime();
    
    //Give the SubtitleUnit titles to store for access later
    bool setTitles(vector<ofUTF8String> words);
    bool addTitle(ofUTF8String word);
    
    //Remove the ith title from the SubtitleUnit - the removed
    //string is returned upon success
    ofUTF8String removeTitle(int i);
    
    //Get every title contained in the SubtitleUnit
    vector<ofUTF8String> getLines();
    
    void print(); //Debug function
    
protected:
    int index;
    long startTime; //in milliseconds
    long endTime; //in milliseconds
    vector<ofUTF8String> text; //Size limited to max of 2
};


class ofxSubtitles {

public:
    ofxSubtitles();
    ofxSubtitles(string subPath, string fontPath, int fontSize, int fps, textJustification j);
    ~ofxSubtitles();
    
    bool loadSubs(string path); //Constructs subtitle vector 
//  bool loadFont(string path, int fontsize); //Simple font load
//  bool loadFont(string path, int fontsize, bool antiAliased, bool fullCharacterSet, 
//                bool makeContours, bool simplifyAmt, int dpi); //More detailed font load
    
    
    void setJustification(textJustification j);
    void setFramesPerSecond(int fps); //Timecode's default fps is 30
    void setTime(long milliseconds);
    void setTime(float seconds);
    void setTime(int frames);
    void setFadeInterval(long milliseconds);
    
    //Creates a basic, non-bolded/italicized/underlined subtitle
    //void insertSubtitle(string startTime, string endTime, ofUTF8String subtitleText);
    //Allows you control over bolding, italics, and underlines
    //void insertSubtitle(string startTime, string endTime, ofUTF8String subtitleText, bool bold, bool ital, bool underl);
    //void removeSubtitle(int subtitleNumber); 
    void drawToScreen(float x, float y);
    
    ofTrueTypeFont* font;
    
protected:
    
    string filepath;
    bool subsLoaded;
    long fadeTime; //In milliseconds
    long currentTime; //In milliseconds
    
    ofBuffer srtFile;
    vector<SubtitleUnit> subtitleList;    
    textJustification subsJustification;
    SubtitleUnit *currentlyDisplayedSub;
    
    ofRectangle textBounds;
    
    ofxTimecode timecode;

    SubtitleUnit* searchSubtitleList(int minIndex, int maxIndex, long elapsedTime);
};


#endif
