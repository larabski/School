#include "AllClipsTab.hpp"

//--------------------------------------------------------------

AllClipsTab::AllClipsTab(string label, int x, int y) {
  tab = new Tab(label, x, y, true);
  tab->setActive();
  XMLFileAgent fileAgent = XMLFileAgent();
  vector<Metadata> allVideosMetadatas = fileAgent.loadMetadataForAllVideos();
  videoGrid = new VideoGrid(allVideosMetadatas, "AllClips");
}

//--------------------------------------------------------------

void AllClipsTab::update() {
  tab->update();
  if (tab->isActive()) videoGrid->update();
}

//--------------------------------------------------------------

void AllClipsTab::draw() {
  tab->draw();
  if (!tab->isActive()) return;
  if (videoGrid->isEmpty()) {
    ofSetHexColor(Colors::CHARCOAL_GRAY);
    ofDrawBitmapString("No Clips Imported.", 600, 235);
  } else {
    videoGrid->draw();
  }
}

//--------------------------------------------------------------

void AllClipsTab::attachToEvent(ofEvent<void> tabClickEvent) {
  tab->attachToEvent(tabClickEvent);
}

//--------------------------------------------------------------

void AllClipsTab::setActive() {
  tab->setActive();
}

//--------------------------------------------------------------

void AllClipsTab::setInactive() {
  tab->setInactive();
}
