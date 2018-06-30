#include "PlayerSection.hpp"

//--------------------------------------------------------------

void PlayerSection::setup() {
  
  ImageButtonProps props;
  props.buttonWidth = 40;
  props.buttonHeight = 40;
  props.buttonX = VIDEO_FRAME_X + 410;
  props.buttonY = VIDEO_FRAME_Y + VIDEO_FRAME_HEIGHT + 42;
  props.imageWidth = 40;
  props.imageHeight = 40;
  playButton = new ImageButton("images/play_dark.png", props);
  playButton->setupButton(Colors::DARK_GRAY, Colors::CHARCOAL_GRAY, Colors::CHARCOAL_GRAY, 0.0);
  ofAddListener(Events::playButtonClickEvent, this, &PlayerSection::onPlayButtonClicked);
  playButton->attachToEvent(Events::playButtonClickEvent);
  
  pauseButton = new ImageButton("images/pause.png", props);
  pauseButton->setupButton(Colors::DARK_GRAY, Colors::CHARCOAL_GRAY, Colors::CHARCOAL_GRAY, 0.0);
  ofAddListener(Events::pauseButtonClickEvent, this, &PlayerSection::onPauseButtonClicked);
  pauseButton->attachToEvent(Events::pauseButtonClickEvent);
  
  props.buttonX = VIDEO_FRAME_X + 450;
  
  stopButton = new ImageButton("images/stop.png", props);
  stopButton->setupButton(Colors::DARK_GRAY, Colors::CHARCOAL_GRAY, Colors::CHARCOAL_GRAY, 0.0);
  ofAddListener(Events::stopButtonClickEvent, this, &PlayerSection::onStopButtonClicked);
  stopButton->attachToEvent(Events::stopButtonClickEvent);
  
  ofAddListener(Events::playVideoButtonClickEvent, this, &PlayerSection::setupVideoPlayer);
  ofAddListener(Events::playTimelineButtonClickEvent, this, &PlayerSection::setupVideoPlayer);
  ofAddListener(Events::fadeButtonSelectedEvent, this, &PlayerSection::setIsSetToFade);
  
}

//--------------------------------------------------------------

void PlayerSection::update() {
  if (!videosToPlay.empty()) {
    player.back().update();
  }
  updateVideoButtons();
}

//--------------------------------------------------------------

void PlayerSection::draw() {
  
  drawBackground();
  
  drawVideoTitle();
  drawVideo();
  
  float position = 0.0;
  
  if (!videosToPlay.empty()) {
    position = player.back().getPosition();
    if (position > 0.0) {
      elapsedTime = (position * player.back().getDuration()) + totalElapsedTime;
    }
  } else {
    elapsedTime = 0;
  }
  
  drawVideoProgressBar(elapsedTime, totalVideoTime);
  drawVideoTimer(elapsedTime, totalVideoTime);
  
  drawVideoButtons();
}

//--------------------------------------------------------------

void PlayerSection::onPlayButtonClicked(){
  if (!videosToPlay.empty()) {
    player.back().setPaused(false);
  } else {
    setupVideoPlayer(allVideos);
  }
}

//--------------------------------------------------------------

void PlayerSection::onPauseButtonClicked(){
  player.back().setPaused(true);
}

//--------------------------------------------------------------

void PlayerSection::onStopButtonClicked(){
  if (!videosToPlay.empty()) {
    player.back().setPaused(true);
  }
  ofNotifyEvent(Events::playbackStopEvent);
}

//--------------------------------------------------------------

void PlayerSection::setIsSetToFade(bool &isSetToFade){
  this->isSetToFade = isSetToFade;
}

//--------------------------------------------------------------

void PlayerSection::setupVideoPlayer(vector<std::string> &videosToPlay){
  totalVideoTime = 0.0;
  totalElapsedTime = 0;
  this->videosToPlay = videosToPlay;
  allVideos = videosToPlay;
  vector<ofVideoPlayer> player;
  this->player = player;
  for (int i = 0; i < videosToPlay.size(); i++) {
    ofVideoPlayer p;
    this->player.push_back(p);
    this->player.at(i).load("videos/" + videosToPlay.at(i));
    this->player.at(i).setLoopState(OF_LOOP_NONE);
    totalVideoTime += this->player.at(i).getDuration();
  }
  this->player.back().play();
}

//--------------------------------------------------------------

void PlayerSection::drawBackground() {
  //Setup background color
  ofSetHexColor(Colors::WHITE);
  ofDrawRectangle(0, 0, bounds.width, bounds.height);
}

//--------------------------------------------------------------

void PlayerSection::drawVideoTitle() {
  ofSetHexColor(Colors::BLACK);
  std:string videoName;
  if (!videosToPlay.empty()) {
    if (allVideos.size() == 1) {
      videoName = PLAYING_CLIP + "\"" + videosToPlay.back() + "\"";
    } else {
      videoName = PLAYING_TIMELINE_CLIP + "\"" + videosToPlay.back() + "\"";
    }
  } else {
    videoName = "No video currently playing.";
  }
  ofDrawBitmapString(videoName, VIDEO_FRAME_X, 30);

}

//--------------------------------------------------------------

void PlayerSection::drawVideo(){
  
  //Draw video frame
  ofSetHexColor(Colors::GHOST_GRAY);
  ofDrawRectangle(VIDEO_FRAME_X, VIDEO_FRAME_Y, VIDEO_FRAME_WIDTH, VIDEO_FRAME_HEIGHT);
  ofSetHexColor(Colors::WHITE);
  
  if (!videosToPlay.empty()) {
    if (player.back().getIsMovieDone()) {
      videosToPlay.pop_back();
      player.pop_back();
      int timeLeftToPlay = 0;
      for (int i = 0; i < player.size(); i++) {
         timeLeftToPlay += player.at(i).getDuration();
      }
      totalElapsedTime = totalVideoTime - timeLeftToPlay;
      if (!videosToPlay.empty()) {
        player.back().play();
      }
    } else {
      //Draw video
      if (isSetToFade) {
        setVideoFade();
      }
      /*ofPixels px = player.back().getPixels();
      ofImage videoFrame;
      
      for (int i = 0; i < px.getWidth(); i++){
        for (int j = 0; j < px.getHeight(); j++){
          ofColor color = px.getColor(i, j);
          float red = color.r - 100 >= 0 ? color.r - 100 : color.r;
          float green = color.g - 100 >= 0 ? color.g - 100 : color.g;
          float blue = color.b - 100 >= 0 ? color.b - 100 : color.b;
          color.set(red, green, blue);
          px.setColor(i,j,color);
        }
      }
      videoFrame.setFromPixels(px);
      videoFrame.draw(VIDEO_X, VIDEO_Y, VIDEO_WIDTH, VIDEO_HEIGHT);*/
      player.back().draw(VIDEO_X, VIDEO_Y, VIDEO_WIDTH, VIDEO_HEIGHT);
    }
  } else {
    //Video Ended
    ofSetHexColor(Colors::BLACK);
    ofDrawRectangle(VIDEO_X, VIDEO_Y, VIDEO_WIDTH, VIDEO_HEIGHT);
  }
}

//--------------------------------------------------------------

void PlayerSection::setVideoFade(){
  float videoLength = player.back().getDuration();
  float videoElapsedTime = player.back().getPosition() * videoLength;
  float videoTimeRemaining = videoLength - videoElapsedTime;
  float fadeTime = 2.0;
  ofEnableAlphaBlending();
  if (player.back().getPosition() > 0) {
    if (videoTimeRemaining < fadeTime) {
      int colorToFade = 255 * videoTimeRemaining / fadeTime;
      ofSetColor(colorToFade, colorToFade, colorToFade, 255);
    } else {
      ofSetColor(255, 255, 255, 255);
    }
  } else {
    ofSetHexColor(Colors::BLACK);
  }
}

//--------------------------------------------------------------

void PlayerSection::drawVideoProgressBar(int elapsedTime, int duration){
  //Draw video progress bar
  
  ofSetHexColor(Colors::GHOST_GRAY);
  ofDrawRectangle(PROGRESS_BAR_X, PROGRESS_BAR_Y, VIDEO_FRAME_WIDTH, PROGRESS_BAR_HEIGHT);
  
  ofSetHexColor(Colors::BLACK);
  int progressBarWidth = 0;
  if (!videosToPlay.empty()) {
    progressBarWidth = timeFormater.getElapsingBarWidth(elapsedTime, (int) duration, VIDEO_FRAME_WIDTH);
  }
  ofDrawRectangle(PROGRESS_BAR_X, PROGRESS_BAR_Y, progressBarWidth , PROGRESS_BAR_HEIGHT);
}

//--------------------------------------------------------------

void PlayerSection::drawVideoTimer(int elapsedTime, int duration){
  
  //Draw video timer
  const int elapsedSeconds = timeFormater.getSeconds(elapsedTime);
  const int elapsedMinutes = timeFormater.getMinutes(elapsedTime);
  
  const int totalSeconds = timeFormater.getSeconds((int) duration);
  const int totalMinutes = timeFormater.getMinutes((int) duration);
  
  const std::string elapsedMinutesString = timeFormater.formatWithTwoDecimalNumbers(elapsedMinutes);
  const std::string elapsedSecondsString = timeFormater.formatWithTwoDecimalNumbers(elapsedSeconds);
  const std::string totalMinutesString = timeFormater.formatWithTwoDecimalNumbers(totalMinutes);
  const std::string totalSecondsString = timeFormater.formatWithTwoDecimalNumbers(totalSeconds);
  
  ofSetHexColor(Colors::CHARCOAL_GRAY);
  ofDrawBitmapString(elapsedMinutesString + ":" + elapsedSecondsString, VIDEO_FRAME_X, VIDEO_FRAME_Y + VIDEO_FRAME_HEIGHT + 60);
  ofDrawBitmapString(totalMinutesString + ":" + totalSecondsString, VIDEO_FRAME_X + VIDEO_FRAME_WIDTH - 40, VIDEO_FRAME_Y + VIDEO_FRAME_HEIGHT + 60);
}

//--------------------------------------------------------------

void PlayerSection::drawVideoButtons(){
  if (!videosToPlay.empty()) {
    if (!player.back().isPaused()) {
      pauseButton->draw();
    } else {
      playButton->draw();
    }
  } else {
    playButton->draw();
  }
  stopButton->draw();
}

//--------------------------------------------------------------

void PlayerSection::updateVideoButtons(){
  if (!videosToPlay.empty()) {
    if (!player.back().isPaused()) {
      pauseButton->update();
    } else {
      playButton->update();
    }
  } else {
    playButton->update();
  }
  stopButton->update();
}

