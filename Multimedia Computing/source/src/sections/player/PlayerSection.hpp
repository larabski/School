#ifndef PlayerSection_hpp
#define PlayerSection_hpp

#include <stdio.h>

#include "Section.h"
#include "ofxDatGui.h"
#include "ImageButton.hpp"
#include "TimeFormater.h"
#include "Bounds.h"
#include "Events.hpp"
#include "Dimensions.h"

class PlayerSection : public Section {
  
public:
  
  void setup();
  void update();
  void draw();
  
  void setupVideoPlayer(vector<std::string> &videosToPlay);
  
  void drawBackground();
  void drawVideoTitle();
  void drawVideo();
  void setVideoFade();
  void drawVideoProgressBar(int elapsedTime, int duration);
  void drawVideoTimer(int elapsedTime, int duration);
  void setIsSetToFade(bool &isSetToFade);
  void drawVideoButtons();
  void updateVideoButtons();
  
  void onPlayButtonClicked();
  void onPauseButtonClicked();
  void onStopButtonClicked();
  
private:
  
  vector<ofVideoPlayer> player;
  vector<std::string> videosToPlay;
  vector<std::string> allVideos;
  TimeFormater timeFormater;
  ImageButton *playButton;
  ImageButton *pauseButton;
  ImageButton *stopButton;
  
  float totalVideoTime;
  int totalElapsedTime;
  int elapsedTime;
  bool isSetToFade = false;
  
  const int VIDEO_WIDTH = Dimensions::WINDOW_WIDTH-140;
  const int VIDEO_HEIGHT = Dimensions::WINDOW_HEIGHT-160;
  const int VIDEO_X = 70;
  const int VIDEO_Y = 50;
  const int VIDEO_FRAME_WIDTH = Dimensions::WINDOW_WIDTH-136;
  const int VIDEO_FRAME_HEIGHT = Dimensions::WINDOW_HEIGHT-156;
  const int VIDEO_FRAME_X = 68;
  const int VIDEO_FRAME_Y = 48;
  const int PROGRESS_BAR_X = VIDEO_FRAME_X;
  const int PROGRESS_BAR_Y = VIDEO_FRAME_Y + VIDEO_FRAME_HEIGHT + 30;
  const int PROGRESS_BAR_HEIGHT = 2;
  
  const int width = Dimensions::WINDOW_WIDTH;
  const int height = Dimensions::WINDOW_HEIGHT;
  const int x = 0;
  const int y = 0;
  
  const Bounds bounds = { x, y, width, height };
  
  const std::string PLAYING_CLIP = "Playing Clip: ";
  const std::string PLAYING_TIMELINE_CLIP = "Playing Timeline Clip: ";
  
};


#endif /* PlayerSection_hpp */
