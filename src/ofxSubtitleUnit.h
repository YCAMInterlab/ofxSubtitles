

#pragma once

#include "ofMain.h"
#include "ofxTimecode.h"
//#define MAX_LINES_PER_SUB_UNIT 2

enum ofxSubtitleJustification {
    TEXT_JUSTIFICATION_LEFT,
    TEXT_JUSTIFICATION_CENTER,
    TEXT_JUSTIFICATION_RIGHT
};

class ofxSubtitleUnit {
    
  public:
    
    //Set the index of the ofxSubtitleUnit within a larger set of
    //ofxSubtitleUnits
    void setIndex(int i);
    int getIndex();
    
    //Set and get start and end times
    void setStartTime(long millis);
    long getStartTime();
    
    void setEndTime(long millis);
    long getEndTime();
    
    //Give the ofxSubtitleUnit titles to store for access later
    bool setTitles(vector<string> words);
    bool addTitle(string word);
    
    //Remove the ith title from the ofxSubtitleUnit - the removed
    //string is returned upon success
    string removeTitle(int i);
    
    //Get every title contained in the ofxSubtitleUnit
    vector<string>& getLines();
    
    void print(); //Debug function
    
    inline friend ostream& operator<<(ostream& os, const ofxSubtitleUnit& su) {
        os << su.index << endl;
        os << ofxTimecode::timecodeForMillis(su.startTime, ",") << " --> " << ofxTimecode::timecodeForMillis(su.endTime, ",") << endl;
        
        for(int i = 0; i < su.text.size(); i++){
            os << su.text[i] << endl;
        }
        os << endl;
        return os;
    }

protected:
    int index;
    long startTime; //in milliseconds
    long endTime; //in milliseconds
    vector<string> text; //Size limited to max of 2
};
