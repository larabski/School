#include "TimelineSection.hpp"

//--------------------------------------------------------------

void TimelineSection::setup() {
  setupPlayButton();
  setupTransitionsDropdown();
  videoRow = new VideoRow();
  ofAddListener(Events::filtersAppliedEvent, this, &TimelineSection::buildTimelineFromMetadatas);
}

//--------------------------------------------------------------

void TimelineSection::setupPlayButton() {
  playButton = new ofxDatGuiButton("Play");
  playButton->setWidth(Dimensions::SMALL_TAB_WIDTH - Dimensions::UI_PANEL_PADDING - Dimensions::UI_PANEL_PADDING/2);
  playButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  playButton->setStripeVisible(false);

  const int x = Dimensions::UI_PANEL_PADDING;
  const int y = Dimensions::PROPERTIES_SECTION_HEIGHT + Dimensions::UI_PANEL_PADDING;
  playButton->setPosition(x, y);
  playButton->onButtonEvent(this, &TimelineSection::onPlayButtonClicked);
}

//--------------------------------------------------------------

void TimelineSection::setupTransitionsDropdown() {
  vector<string> options = { "No Transition", "Fade Transition" };
  transitionsDropdown = new ofxDatGuiDropdown("", options);
  transitionsDropdown->setStripeVisible(false);
  transitionsDropdown->setTheme(new ofxDatGuiThemeWireframe());
  transitionsDropdown->setWidth(playButton->getWidth());
  transitionsDropdown->collapse();
  transitionsDropdown->select(0);

  const int x = playButton->getX() + playButton->getWidth() + Dimensions::UI_PANEL_PADDING;
  const int y = playButton->getY();
  transitionsDropdown->setPosition(x, y);
}

//--------------------------------------------------------------

void TimelineSection::buildTimelineFromMetadatas(vector<Metadata> &metadatas) {
  videoRow = new VideoRow(metadatas);
}

//--------------------------------------------------------------

void TimelineSection::onPlayButtonClicked(ofxDatGuiButtonEvent event) {
  vector<string> videoNames = videoRow->getVideoNames();
  if (videoNames.empty()) return;
  /** We need them reversed when passing to the Player State. */
  std::reverse(videoNames.begin(), videoNames.end());
  /**
   What transition did the user select (if any)?
   */
  const string transitionPicked = transitionsDropdown->getSelected()->getLabel();
  bool isSetToFade = transitionPicked == "Fade Transition";
  ofNotifyEvent(Events::fadeButtonSelectedEvent, isSetToFade, this);
  /**
   Video & trasition all set -> notify to start actually playing.
   */
  ofNotifyEvent(Events::playTimelineButtonClickEvent, videoNames, this);
}

//--------------------------------------------------------------

void TimelineSection::update() {
  videoRow->update();
  playButton->update();
  transitionsDropdown->update();
}

//--------------------------------------------------------------

void TimelineSection::draw() {
  ofSetHexColor(Colors::LIGHT_GRAY);
  ofDrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height);
  videoRow->draw();
  playButton->draw();
  transitionsDropdown->draw();
}
