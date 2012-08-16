//
//  ofxSubtitleUnit.cpp
//  SubtitlesTimingEditor
//
//  Created by Jim on 8/16/12.
//
//

#include "ofxSubtitleUnit.h"
/*----------------------------------------------------------------------------
 
 ofxSubtitleUnit
 
 ---------------------------------------------------------------------------*/

void ofxSubtitleUnit::setIndex(int i){
    index = i;
}


int ofxSubtitleUnit::getIndex(){
    return index;
}


void ofxSubtitleUnit::setStartTime(long millis){
    startTime = millis;
}


long ofxSubtitleUnit::getStartTime(){
    return startTime;
}


void ofxSubtitleUnit::setEndTime(long millis){
    endTime = millis;
}


long ofxSubtitleUnit::getEndTime(){
    return endTime;
}

bool ofxSubtitleUnit::setTitles(vector<string> subtitleStrings){
    if(subtitleStrings.size() < MAX_LINES_PER_SUB_UNIT){
        text = subtitleStrings;
        return true;
    }
    return false;
}


bool ofxSubtitleUnit::addTitle(string subtitleString){
    if(text.size() < MAX_LINES_PER_SUB_UNIT){
        text.push_back(subtitleString);
        return true;
    }
    return false;
}

string ofxSubtitleUnit::removeTitle(int i){
    if(i >= text.size() || i < 0){
        ofLogError("Title index out of bounds.");
        return "";
    }
    string removedTitle = text[i];
    text.erase(text.begin()+i);
    return removedTitle;
}


vector<string>& ofxSubtitleUnit::getLines(){
    return text;
}

void ofxSubtitleUnit::print(){
    cout << index << endl;
    cout << startTime << " --> " << endTime << endl;
    
    for(int i = 0; i < text.size(); i++){
        cout << text[i] << endl;
    }
    
    cout << endl;
}
