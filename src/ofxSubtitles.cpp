//
//  ofxSubtitles.cpp
//  
//
//  Created by Andrew Bueno on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

ofxSubtitles::ofxSubtitles(string subPath, string fontPath, int fps){
    subsLoaded = loadSubs(subPath);
    fontLoaded = loadFont(fontPath);
    setFPS(fps);
}

ofxSubtitles::~ofxSubtitles(){
    
}


bool ofxSubtitles::loadSubs(string path){
    subtitles = ofBufferFromFile(path);
    
    if(subtitles = NULL || (path.substr(path.length - 4, 4).compare(".srt") != 0)){
        ofLogError("Invalid subtitle file path. Check to see if you misspelled the path, that the file does not exist, or that the file is not a .srt");
        subsLoaded = false;
    }
    else{
        ofUTF8String line = subtitles.getFirstLine();
        while(!subtitles.isLastLine()){
            Subtitle title;
            title->index = int(line);
            
            //Fill the new subtitle struct with its start and end times
            line = subtitles.getNextLine();
            vector<string> times = ofSplitString(line, " ");
            Subtitle->startTime = timecode.millisForMSTimecode(times[0]);
            Subtitle->endTime = timecode.millisForMSTimecode(times[2]);
            line = subtitles.getNextLine();
            
            //Add each spoken line to the subtitle struct
            while(line.compare("") == 0){
                title->text.push_back(line);
                line = subtitles.getNextLine();
            }
            
            subs.push_back(title);
            line = subtitles.getNextLine(); //This should be the number of the next subtitle in the .srt,
                                            //or empty if the end of the buffer has been reached.
        }
        
        subsLoaded = true;
    }
}


void ofxSubtitles::loadFont(string path, int fontsize){
    font.loadFont(path, fontsize);
    
    if(!font.isLoaded()){
        ofLogError("Invalid font file path. Check to see if you misspelled the path, that the file does not exist, or that the file is not a .srt");

        fontLoaded = false;
    }
    else subsLoaded = true;
}


bool ofxSubtitles::loadFont(string path, int fontsize, bool antiAliased, bool fullCharacterSet, 
                            bool makeContours, bool simplifyAmt, int dpi){
    
    font.loadFont(path, fontsize, antiAliased, fullCharacterSet, makeContours, 
                  simplifyAmt, dpi);
    
    if(!font.isLoaded()){
        ofLogError("Invalid font file path. Check to see if you misspelled the path, or that the file does not exist.");
        return false;
    }
    else return true;
}

void ofxSubtitles::setFPS(int fps){
    timecode.setFPS(fps);
}
       

void ofxSubtitles::setTime(long milliseconds){
    currentTime = milliseconds;
}


void ofxSubtitles::setTime(float seconds){
    currentTime = seconds * 1000;
}

//PLEASE MAKE SURE that you have your frame rate set correctly!
void ofxSubtitles::setTime(int frames){
    currentTime = timeCode.millisForFrame(frames);
}

void ofxSubtitles::setFadeInterval(long milliseconds){
    fadeTime = milliseconds;
}

void ofxSubtitles::draw(float x, float y){
    
}

void ofxSubtitles::draw(ofPoint p, int w, int h){
    
}
