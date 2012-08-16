#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
//    vector<string> harblar = ofSplitString("00:45:23,100", ",:");
//    cout << harblar.size() << endl;
    
    ofBackground(0, 0, 0);
    subtitles.setup("take_cover.srt", "futurah.ttf", 24, 29.97, TEXT_JUSTIFICATION_CENTER);
    playerRect.set(0, 0, 720, 480);
    player.loadMovie("take_cover.mp4");
    player.setLoopState(OF_LOOP_NORMAL);
    player.play();
    
}

//--------------------------------------------------------------
void testApp::update(){
    player.idleMovie();
    

        subtitles.setTimeInSeconds(player.getPosition() * player.getDuration());
        cout << player.getPosition()  << " " << subtitles.currentTime << endl;

    
}

//--------------------------------------------------------------
void testApp::draw(){
    player.draw(playerRect);
    subtitles.draw(360, 400);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}