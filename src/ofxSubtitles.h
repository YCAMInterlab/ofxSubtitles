//
//  ofxSubtitles.h
//  
//
//  Created by Andrew Bueno on 7/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ofxSubtitles_h
#define _ofxSubtitles_h
#include <iostream>
#include "ofMain.h"
#include "ofxTimecode.h"
#include "ofFile.h"
#include "ofFileUtils.h"
#include "ofxUnicode.h"


class ofxSubtitles {
    public:
        ofxSubtitles(string subPath, string fontPath, int fps);
        ~ofxSubtitles();
    
        bool subsLoaded;
        bool fontLoaded;
    
        bool loadSubs(string path); //Constructs subtitle vector 
        bool loadFont(string path, int fontsize); //Simple font load
        bool loadFont(string path, int fontsize, bool antiAliased, bool fullCharacterSet, 
                  bool makeContours, bool simplifyAmt, int dpi); //More detailed font load
    
        void setFPS(int fps); //Timecode's default fps is 30
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
    
        vector<Subtitle> subs;
    
    protected:
    
//        typedef struct AppearanceMarkers{
//            ofColor color;
//            bool bold;
//            bool italics;
//            bool underlined;
//        }Appearance;
                             
        typedef struct SubtitleUnit{
            int index; //Within the subs vector, essentially the number given for the sub in the .srt,
                       //assuming you don't insert another subtitle independently of the file you give
            long startTime; //In milliseconds
            long endTime; //In milliseconds
            //Appearance lineTypography[2]; //Array parallel to subtitle lines that marks if each line
                                               //is italicized, bolded, etc.
            vector<string> text; //I'm keeping the number of lines to 2 to avoid too much clutter on the screen
        }Subtitle;
    
        ofxTimecode timecode;
        Subtitle currentlyDisplayedSub;
        string filepath;
        long fadeTime;
        float currentTime; //In milliseconds
        ofTrueTypeFont font;
}


#endif
