//
//  ofxSubtitles.cpp
//  
//
//  Created by Andrew Bueno on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  @The Studio for Creative Inquiry

#include <iostream>

/*----------------------------------------------------------------------------
 
                                SubtitleUnit 
 
 ---------------------------------------------------------------------------*/

void SubtitleUnit::setIndex(int i){
    index = i;
}


void SubtitleUnit::getIndex(){
    return index;
}


void SubtitleUnit::setStartTime(long millis){
    startTime = millis;
}


long SubtitleUnit::getStartTime(){
    return startTime;
}


void SubtitleUnit::setEndTime(long millis){
    endTime = millis;
}


long SubtitleUnit::getEndTime(){
    return endTime;
}


bool SubtitleUnit::setTitles(vector<ofUTF8String> phrases){
    if(phrases.size() < 3){
        text = words;
        return true;
    }
    else return false;
}


bool SubtitleUnit::addTitle(ofUTF8String phrase){
    if(text.size() < 2){
        text.push_back(phrase);
        return true;
    }
    else return false;
}


UTF8String SubtitleUnit::removeTitle(int i){
    if(i > (text.size() - 1) || i < 0){
        ofLogError("Title index out of bounds.");
        return NULL;
    }
    else{
        UTF8String removedTitle = text[i];
        text.erase(i);
        return removedTitle;
    }
}


vector<UTF8String> SubtitleUnit::getText(){
    return text;
}


void SubtitleUnit::print(){
    cout << index << endl;
    cout << startTime << " --> " << endTime << endl;
    
    for(int i = 0; i < text.size(); i++){
        cout << text[i] << endl;
        cout << endl;
    }
    
    cout << endl;
}

/*----------------------------------------------------------------------------
 
                                ofxSubtitles 
 
 ---------------------------------------------------------------------------*/

ofxSubtitles::ofxSubtitles(string subPath, string fontPath, int fontSize, int fps){
    subsLoaded = loadSubs(subPath);
    font.loadFont(fontPath, fontSize);
    setFramesPerSecond(fps);
}

ofxSubtitles::~ofxSubtitles(){
    
}


bool ofxSubtitles::loadSubs(string path){
    srtFile = ofBufferFromFile(path);
    
    if(srtFile = NULL || (path.substr(path.length - 4, 4).compare(".srt") != 0)){
        ofLogError("Invalid subtitle file path. Check to see if you misspelled the path, that the file does not exist, or that the file is not a .srt");
        subsLoaded = false;
    }
    else{
        ofUTF8String line = srtFile.getFirstLine();
        while(!srtFile.isLastLine()){
            SubtitleUnit title;
            title.setIndex = int(line);
            
            //Fill the new subtitle struct with its start and end times
            line = srtFile.getNextLine();
            vector<string> times = ofSplitString(line, " ");
            title.setStartTime(timecode.millisForMSTimecode(times[0]));
            title.setEndTime(timecode.millisForMSTimecode(times[2]));
            line = srtFile.getNextLine();
            
            //Add each spoken line to the subtitle struct
            while(line.compare("") == 0){
                title.addTitle(line);
                line = srtFile.getNextLine();
            }
            
            subtitleList.push_back(title);
            line = srtFile.getNextLine(); //This should be the number of the next subtitle in the .srt,
                                            //or empty if the end of the buffer has been reached.
        }
        
        subsLoaded = true;
    }
}


//void ofxSubtitles::loadFont(string path, int fontsize){
//    font.loadFont(path, fontsize);
//    
//    if(!font.isLoaded()){
//        ofLogError("Invalid font file path. Check to see if you misspelled the path, that the file does not exist, or that the file is not a .srt");
//
//        fontLoaded = false;
//    }
//    else subsLoaded = true;
//}
//
//
//bool ofxSubtitles::loadFont(string path, int fontsize, bool antiAliased, bool fullCharacterSet, 
//                            bool makeContours, bool simplifyAmt, int dpi){
//    
//    font.loadFont(path, fontsize, antiAliased, fullCharacterSet, makeContours, 
//                  simplifyAmt, dpi);
//    
//    if(!font.isLoaded()){
//        ofLogError("Invalid font file path. Check to see if you misspelled the path, or that the file does not exist.");
//        return false;
//    }
//    else return true;
//}

void ofxSubtitles::setFramesPerSecond(int fps){
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
