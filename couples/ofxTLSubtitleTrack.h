//
//  ofxTLSubtitles.h
//  SubtitlesTimingEditor
//
//  Created by Jim on 8/16/12.
//
//

#pragma once
#include "ofxTimeline.h"
#include "ofxSubtitles.h"

// a TL subtitle is controlled like a switch but has reference
// to a ofxSubtitleUnit letting it edit the SRT file
class ofxTLSubtitle : public ofxTLSwitch {
  public:
  	ofxSubtitleUnit* subtitleUnit;
    
};

class ofxTLSubtitleTrack : public ofxTLSwitcher {
  public:
    ofxTLSubtitleTrack();
    virtual ~ofxTLSubtitleTrack();
    
    //access this to load the font
    ofxSubtitles& getSubtitles();
    
    virtual void mouseReleased(ofMouseEventArgs& args, long millis);
    
    virtual void loadSRT(string srtPath);
    virtual void reloadSRT(); //in case you are editing externally
    virtual void saveSRT(string srtPath);
    virtual void saveSRT();
    
//    virtual void load();
//	virtual void save();
    
protected:
    ofxSubtitles subtitles;
    
    virtual ofxTLKeyframe* newKeyframe();
    virtual void restoreKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);
	virtual void storeKeyframe(ofxTLKeyframe* key, ofxXmlSettings& xmlStore);
};

