#pragma once

#include "ofMain.h"
#include "State.h"
#include "Metadata.hpp"
#include "MainState.hpp"
#include "PlayerState.hpp"
#include "ProcessVideoAgent.hpp"

class ofApp : public ofBaseApp {

public:
  
  void setup();
  void update();
  void draw();
  
  void onPlaybackStop();
  void onPlayVideoButtonClick(vector<string> &videosToPlay);
  
private:
  
  State *mainState = new MainState;
  State *playerState = new PlayerState;
  bool isPlayingVideo = false;

};
