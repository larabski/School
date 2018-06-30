#include "TimelineClipsTab.hpp"

//--------------------------------------------------------------

TimelineClipsTab::TimelineClipsTab(string label, int x, int y) {
  tab = new Tab(label, x, y, true);
  tab->setInactive();
  videoGrid = new VideoGrid("TimelineClips");
  ofAddListener(Events::filtersAppliedEvent, this, &TimelineClipsTab::buildGridFromMetadatas);
}

//--------------------------------------------------------------

void TimelineClipsTab::buildGridFromMetadatas(vector<Metadata> &metadatas) {
  videoGrid = new VideoGrid(metadatas, "TimelineClips");
}

//--------------------------------------------------------------

void TimelineClipsTab::update() {
  tab->update();
  if (tab->isActive()) videoGrid->update();
}

//--------------------------------------------------------------

void TimelineClipsTab::draw() {
  tab->draw();
  if (!tab->isActive()) return;
  if (videoGrid->isEmpty()) {
    ofSetHexColor(Colors::CHARCOAL_GRAY);
    ofDrawBitmapString("No Timeline Created.", 600, 235);
  } else {
    videoGrid->draw();
  }
}

//--------------------------------------------------------------

void TimelineClipsTab::attachToEvent(ofEvent<void> tabClickEvent) {
  tab->attachToEvent(tabClickEvent);
}

//--------------------------------------------------------------

void TimelineClipsTab::setActive() {
  tab->setActive();
}

//--------------------------------------------------------------

void TimelineClipsTab::setInactive() {
  tab->setInactive();
}
