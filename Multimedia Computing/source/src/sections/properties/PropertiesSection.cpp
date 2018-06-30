#include "PropertiesSection.hpp"

//--------------------------------------------------------------

void PropertiesSection::setup() {
  filtersTab = new FiltersTab(FILTERS_TAB_LABEL, 0, 0);
  ofAddListener(Events::filtersTabClickEvent, this, &PropertiesSection::onFiltersButtonClicked);
  filtersTab->attachToEvent(Events::filtersTabClickEvent);

  videoSettingsTab = new VideoSettingsTab(VIDEO_SETTINGS_TAB_LABEL, Dimensions::SMALL_TAB_WIDTH, 0);
  ofAddListener(Events::videoSettingsTabClickEvent, this, &PropertiesSection::onVideoSettingsButtonClicked);
  videoSettingsTab->attachToEvent(Events::videoSettingsTabClickEvent);
  
  ofAddListener(Events::videoSingleClickEvent, this, &PropertiesSection::onVideoSingleClicked);
}

//--------------------------------------------------------------

void PropertiesSection::onFiltersButtonClicked() {
  filtersTab->setActive();
  videoSettingsTab->setInactive();
}

//--------------------------------------------------------------

void PropertiesSection::onVideoSettingsButtonClicked() {
  filtersTab->setInactive();
  videoSettingsTab->setActive();
}

//--------------------------------------------------------------

void PropertiesSection::onVideoSingleClicked(Metadata &videoMetadata) {
  filtersTab->setInactive();
  videoSettingsTab->setActive(videoMetadata);
}

//--------------------------------------------------------------

void PropertiesSection::update() {
  filtersTab->update();
  videoSettingsTab->update();
}

//--------------------------------------------------------------

void PropertiesSection::draw() {
  ofSetHexColor(Colors::WHITE);
  ofDrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height);
  filtersTab->draw();
  videoSettingsTab->draw();
}
