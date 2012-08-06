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
#include "ofFile.h"
#include "ofFileUtils.h"
#include "ofxUnicode.h"

#define MAX_LINES_PER_SUBTITLE_UNIT 2

class SubtitleUnit{

public:
    SubtitleUnit();
    
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
    UTF8String removeTitle(int i);
    
    //Get every title contained in the SubtitleUnit
    vector<ofUTF8String> getText();
    
    void print(); //Debug function
    
protected:
    int index;
    long startTime;
    long endTime;
    vector<ofUTF8String> text; //Size limited to max of 2
}


class ofxSubtitles {

public:
    ofxSubtitles(string subPath, string fontPath, int fps);
    ~ofxSubtitles();
    
    bool subsLoaded;
    
    bool loadSubs(string path); //Constructs subtitle vector 
//  bool loadFont(string path, int fontsize); //Simple font load
//  bool loadFont(string path, int fontsize, bool antiAliased, bool fullCharacterSet, 
//                bool makeContours, bool simplifyAmt, int dpi); //More detailed font load
    
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
    void draw(ofPoint p);
    void draw(int x, int y);
    
    ofTrueTypeFont font;
    
protected:
    vector<SubtitleUnit> subtitleList;
    ofxTimecode timecode;
    ofBuffer srtFile;
    Subtitle currentlyDisplayedSub;
    string filepath;
    long fadeTime;
    long currentTime; //In milliseconds
}


#endif
