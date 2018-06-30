#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {
  mainState->setup();
  playerState->setup();
  ofAddListener(Events::playbackStopEvent, this, &ofApp::onPlaybackStop);
  ofAddListener(Events::playVideoButtonClickEvent, this, &ofApp::onPlayVideoButtonClick);
  ofAddListener(Events::playTimelineButtonClickEvent, this, &ofApp::onPlayVideoButtonClick);
}

//--------------------------------------------------------------

void ofApp::update() {
  if (!isPlayingVideo) {
    mainState->update();
  } else {
    playerState->update();
  }
}

//--------------------------------------------------------------

void ofApp::draw() {
  if (!isPlayingVideo) {
    mainState->draw();
  } else {
    playerState->draw();
  }
}

//--------------------------------------------------------------

void ofApp::onPlaybackStop() {
  isPlayingVideo = false;
}

//--------------------------------------------------------------

void ofApp::onPlayVideoButtonClick(vector<string> &videosToPlay) {
  isPlayingVideo = true;
}
