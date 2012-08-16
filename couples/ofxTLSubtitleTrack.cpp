//
//  ofxTLSubtitles.cpp
//  SubtitlesTimingEditor
//
//  Created by Jim on 8/16/12.
//
//

#include "ofxTLSubtitleTrack.h"
#include "ofxTimeline.h"

ofxTLSubtitleTrack::ofxTLSubtitleTrack(){
    
}

ofxTLSubtitleTrack::~ofxTLSubtitleTrack(){
    
}

ofxSubtitles& ofxTLSubtitleTrack::getSubtitles(){
    return subtitles;
}

void ofxTLSubtitleTrack::loadSRT(string srtPath){
    clear();
    
    if(subtitles.load(srtPath)){
        vector<ofxSubtitleUnit>& titles = subtitles.getSubtitles();
        for(int i = 0; i < titles.size(); i++){
            ofxTLSubtitle* newTitle = new ofxTLSubtitle();
            newTitle->subtitleUnit = &titles[i];
            newTitle->timeRange.min = newTitle->time = newTitle->subtitleUnit->getStartTime();
            newTitle->timeRange.max = newTitle->subtitleUnit->getEndTime();
            newTitle->startSelected = false;
            newTitle->endSelected   = false;
            keyframes.push_back(newTitle);
        }
    }
    else {
        ofLogError("ofxTLSubtitleTrack") << "Failed to load SRT file " << srtPath << endl;
    }
    
	timeline->flagTrackModified(this);
}

void ofxTLSubtitleTrack::saveSRT(string srtPath){
    //pull current representation into SRT
    
	subtitles.save(srtPath);
}


//void ofxTLSubtitleTrack::load(){
//}
//
//void ofxTLSubtitleTrack::save(){
//    ofxTLSwitcher::save();
//}


ofxTLKeyframe* ofxTLSubtitleTrack::newKeyframe(){
	ofxTLSubtitle* newTitle = new ofxTLSubtitle();
    newTitle->timeRange.min = newTitle->timeRange.max = screenXToMillis(ofGetMouseX());
    newTitle->startSelected = false;
    newTitle->endSelected   = true; //true so you can drag the range to start with
    
    newTitle->subtitleUnit = subtitles.addSubtitle(newTitle->timeRange.min, newTitle->timeRange.max, "", "");
    return newTitle;
}

void ofxTLSubtitleTrack::restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLSwitcher::restoreKeyframe(key, xmlStore);
    ofxTLSubtitle* title = (ofxTLSubtitle*)key;
    title->subtitleUnit->setStartTime(title->timeRange.min);
    title->subtitleUnit->setEndTime(title->timeRange.max);
    title->subtitleUnit->addTitle(xmlStore.getValue("title1", ""));
    title->subtitleUnit->addTitle(xmlStore.getValue("title2", ""));
}

void ofxTLSubtitleTrack::storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore){
    ofxTLSwitcher::storeKeyframe(key, xmlStore);
    ofxTLSubtitle* title = (ofxTLSubtitle*)key;
    if(title->subtitleUnit != NULL){
//	    xmlStore.addValue("title1", title->subtitleUnit->getLines()[0]);
//        xmlStore.addValue("title2", title->subtitleUnit->getLines()[1]);
    }
}
