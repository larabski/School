#include "VideoSection.hpp"

//--------------------------------------------------------------

void VideoSection::setup() {
  allClipsTab = new AllClipsTab(ALL_CLIPS_TAB_LABEL, Dimensions::WINDOW_WIDTH - 2 * Dimensions::LARGE_TAB_WIDTH, 0);
  ofAddListener(Events::allClipsTabClickEvent, this, &VideoSection::onAllClipsTabClicked);
  allClipsTab->attachToEvent(Events::allClipsTabClickEvent);
  
  timelineClipsTab = new TimelineClipsTab(TIMELINE_CLIPS_TAB_LABEL, Dimensions::WINDOW_WIDTH - Dimensions::LARGE_TAB_WIDTH, 0);
  ofAddListener(Events::timelineClipsTabClickEvent, this, &VideoSection::onTimelineClipsTabClicked);
  timelineClipsTab->attachToEvent(Events::timelineClipsTabClickEvent);
  
  const int loadVideoButtonX = Dimensions::WINDOW_WIDTH - 2 * Dimensions::LARGE_TAB_WIDTH - Dimensions::IMPORT_FILE_BUTTON_WIDTH;
  ImageButtonProps props;
  props.buttonWidth = Dimensions::IMPORT_FILE_BUTTON_WIDTH+4;
  props.buttonX = loadVideoButtonX;
  props.buttonY = 0;
  props.imageWidth = 20;
  props.imageHeight = 20;
  loadVideoButton = new LoadVideoButton(BUTTON_IMAGE_PATH, props);
  loadVideoButton->setupButton(Colors::DARK_GRAY, Colors::CHARCOAL_GRAY, Colors::CHARCOAL_GRAY, 1.0);
  ofAddListener(Events::loadVideoEvent, this, &VideoSection::onLoadVideoButtonClicked);
  loadVideoButton->attachToEvent(Events::loadVideoEvent);
}

//--------------------------------------------------------------

void VideoSection::onTimelineClipsTabClicked() {
  allClipsTab->setInactive();
  timelineClipsTab->setActive();
}

//--------------------------------------------------------------

void VideoSection::onAllClipsTabClicked() {
  allClipsTab->setActive();
  timelineClipsTab->setInactive();
}

//--------------------------------------------------------------

void VideoSection::onLoadVideoButtonClicked() {
  loadVideoButton->processOpenFileSelection();
}

//--------------------------------------------------------------

void VideoSection::update() {
  allClipsTab->update();
  timelineClipsTab->update();
  loadVideoButton->update();
}

//--------------------------------------------------------------

void VideoSection::draw() {
  ofSetHexColor(Colors::WHITE);
  ofDrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height);
  allClipsTab->draw();
  timelineClipsTab->draw();
  loadVideoButton->draw();
}
