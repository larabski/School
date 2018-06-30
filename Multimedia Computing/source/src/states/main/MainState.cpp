#include "MainState.hpp"

//--------------------------------------------------------------

void MainState::setup() {
  timelineSection.setup();
  propertiesSection.setup();
  videoSection.setup();
}

//--------------------------------------------------------------

void MainState::update() {
  timelineSection.update();
  propertiesSection.update();
  videoSection.update();
}

//--------------------------------------------------------------

void MainState::draw() {
  propertiesSection.draw();
  videoSection.draw();
  
  // Draw the vertical separator.
  ofSetHexColor(Colors::LIGHT_GRAY);
  ofDrawRectangle(Dimensions::NUM_SMALL_TABS * Dimensions::SMALL_TAB_WIDTH, 26, 1.0, Dimensions::WINDOW_HEIGHT);
  
  timelineSection.draw();
}
