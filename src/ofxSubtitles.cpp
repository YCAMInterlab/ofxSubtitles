//
//  ofxSubtitles.cpp
//  
//
//  Created by Andrew Bueno on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//  @The Studio for Creative Inquiry

#include <iostream>
#include "ofxSubtitles.h"

/*----------------------------------------------------------------------------
 
                                SubtitleUnit 
 
 ---------------------------------------------------------------------------*/

void SubtitleUnit::setIndex(int i){
    index = i;
}


int SubtitleUnit::getIndex(){
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


bool SubtitleUnit::setTitles(vector<ofUTF8String> subtitleStrings){
    if(subtitleStrings.size() < MAX_LINES_PER_SUB_UNIT){
        text = subtitleStrings;
        return true;
    }
    else return false;
}


bool SubtitleUnit::addTitle(ofUTF8String subtitleString){
    if(text.size() < MAX_LINES_PER_SUB_UNIT){
        text.push_back(subtitleString);
        return true;
    }
    else return false;
}


ofUTF8String SubtitleUnit::removeTitle(int i){
    if(i > (text.size() - 1) || i < 0){
        ofLogError("Title index out of bounds.");
        return NULL;
    }
    else{
        ofUTF8String removedTitle = text[i];
        text.erase(text.begin()+i); // myvector.begin()+5
        return removedTitle;
    }
}


vector<ofUTF8String> SubtitleUnit::getLines(){
    return text;
}


void SubtitleUnit::print(){
    cout << index << endl;
    cout << startTime << " --> " << endTime << endl;
    
    for(int i = 0; i < text.size(); i++){
        cout << text[i] << endl;
    }
    
    cout << endl;
}

/*----------------------------------------------------------------------------
 
                                ofxSubtitles 
 
 ---------------------------------------------------------------------------*/

ofxSubtitles::ofxSubtitles(){
    
}

ofxSubtitles::ofxSubtitles(string subPath, string fontPath, int fontSize, int fps,
                           textJustification j){
    subsLoaded = loadSubs(subPath);
    font.loadFont(fontPath, fontSize);
    setFramesPerSecond(fps);
    setJustification(j);
}

ofxSubtitles::~ofxSubtitles(){

}

bool ofxSubtitles::loadSubs(string path){
    srtFile = ofBufferFromFile(path);
    
    bool isNotSRTFile = (path.substr(path.length() - 4, 4).compare(".srt") != 0);
    
    if(&srtFile == NULL || isNotSRTFile){
        ofLogError("Invalid subtitle file path. Check to see if you misspelled the path, that the file does not exist, or that the file is not a .srt");
        subsLoaded = false;
    }
    else{ 
        while(!srtFile.isLastLine()){
            
            //Assign the subtitle unit its index number
            ofUTF8String srtLine = srtFile.getNextLine();
            SubtitleUnit title;
            title.setIndex(ofToInt(srtLine));
            
            //Fill the new subtitle struct with its start and end times
            srtLine = srtFile.getNextLine();
            vector<string> times = ofSplitString(srtLine, " ");
            //cout << "\"" << times[0] << "\"" << endl;
            //cout << "\"" << times[2] << "\"" << endl;
            title.setStartTime(timecode.millisForTimecode(times[0]));
            title.setEndTime(timecode.millisForTimecode(times[2]));
            
            srtLine = srtFile.getNextLine();
            
            //Add each spoken line to the subtitle struct
            while(!srtLine.empty()){
                title.addTitle(srtLine);
                srtLine = srtFile.getNextLine();
            }
            
            subtitleList.push_back(title);
        }
        subsLoaded = true;
    }
}

void ofxSubtitles::setJustification(textJustification j){
        subsJustification = j;
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
    
    int minInd = 0, maxInd = subtitleList.size() - 1;

    //If there is no currently displayed subtitle or the milliseconds parameter falls 
    //outside the scope of the current subtitle, search the list
    
    if(currentlyDisplayedSub == NULL){
        currentlyDisplayedSub = searchSubtitleList(minInd, maxInd, milliseconds);
    }
    else{
        bool pastCurrentTime = (currentlyDisplayedSub->getStartTime() >= milliseconds );
        bool beforeCurrentTime = (currentlyDisplayedSub->getEndTime() <= milliseconds );
        
        if(pastCurrentTime || beforeCurrentTime){
            currentlyDisplayedSub = searchSubtitleList(minInd, maxInd, milliseconds);

        }
    }
}


void ofxSubtitles::setTime(float seconds){
    setTime(seconds * 1000);
}

//PLEASE MAKE SURE that you have your frame rate set correctly in timeCode!
void ofxSubtitles::setTime(int frames){
    setTime(timecode.millisForFrame(frames));
}

void ofxSubtitles::setFadeInterval(long milliseconds){
    fadeTime = milliseconds;
}

//A binary search algorithm for finding a subtitle that should be displaying during the
//specified time. While the datasets are probably small enough that an iterative search
//would do alright, every little bit helps!
SubtitleUnit *ofxSubtitles::searchSubtitleList(int minIndex, int maxIndex, long elapsedTime){
    
    while(minIndex >= maxIndex){
            
        int midIndex = (maxIndex - minIndex)/2 + minIndex;
        
        if(subtitleList[midIndex].getEndTime() <= elapsedTime){
            
            minIndex = midIndex + 1;
        }
        else if(subtitleList[midIndex].getStartTime() >= elapsedTime){
            
            maxIndex = midIndex - 1;
        }
        else{

            return &(subtitleList[midIndex]);
        }
        
    }
    
    return NULL;
}

//Due to the nature of subtitles, this function is designed with the assumption that you
//want to draw text relative to the center of the screen, and will input center x-coordinates
void ofxSubtitles::drawToScreen(float x, float y){
    
    bool canDraw = font.isLoaded() && !(currentlyDisplayedSub == NULL);
    cout << font.isLoaded() << endl;
    if(subsJustification == TEXT_JUSTIFICATION_LEFT && canDraw){
        
        vector<ofUTF8String> subLines = currentlyDisplayedSub->getLines();
        
        for(int i = 0; i < subLines.size(); i++){
            textBounds = font.getStringBoundingBox(subLines[i], 0, 0);
            
            if(i == 0){
                font.drawString(subLines[i], x - textBounds.width, y);
            }
            else{
                font.drawString(subLines[i], x - textBounds.width, y + font.getLineHeight());
            }
        }
        
    }
    else if(subsJustification == TEXT_JUSTIFICATION_CENTER && canDraw){
        
        vector<ofUTF8String> subLines = currentlyDisplayedSub->getLines();
        
        for(int i = 0; i < subLines.size(); i++){
            textBounds = font.getStringBoundingBox(subLines[i], 0, 0);
            
            if(i == 0){
                font.drawString(subLines[i], x - textBounds.width/2, y);
            }
            else{
                font.drawString(subLines[i], x - textBounds.width/2, y + font.getLineHeight());
            }
        }
        
    }
//    else if(subsJustification == RIGHT && canDraw){
//        
//        vector<UTF8String> text = currentlyDisplayedSub.getLines();
//        
//        for(int i = 0; i < currentlyDisplayedSub.getLines().size(); i++){
//            textBounds = font.getStringBoundingBox(text[i], 0, 0);
//            
//            if(i == 0){
//                font.drawString(text[i], x - textBounds.width, drawPoint.y);
//            }
//            else{
//                font.drawString(text[i], x - textBounds.width, drawPoint.y + font.getLineHeight());
//            }
//        }
//    }
}

