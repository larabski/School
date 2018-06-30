#include "Tab.hpp"

//--------------------------------------------------------------

Tab::Tab(string label, int x, int y, bool isLarge) {
  active = false;
  tabButton = new ofxDatGuiButton(label);
  tabButton->setWidth(isLarge ? Dimensions::LARGE_TAB_WIDTH : Dimensions::SMALL_TAB_WIDTH);
  tabButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  tabButton->setBackgroundColor(Colors::WHITE);
  tabButton->setBackgroundColorOnMouseOver(Colors::GHOST_GRAY);
  tabButton->setBackgroundColorOnMouseDown(Colors::GHOST_GRAY);
  tabButton->setPosition(x, y);
  tabButton->setStripeVisible(false);
}

//--------------------------------------------------------------

void Tab::attachToEvent(ofEvent<void> event) {
  attachedEvent = event;
  tabButton->onButtonEvent(this, &Tab::onTabClicked);
}

//--------------------------------------------------------------

void Tab::onTabClicked(ofxDatGuiButtonEvent event) {
  if (active) return;
  ofNotifyEvent(attachedEvent);
}

//--------------------------------------------------------------

void Tab::setActive() {
  active = true;
  tabButton->setLabelColor(Colors::BLACK);
  tabButton->setBackgroundColor(Colors::WHITE);
}

//--------------------------------------------------------------

void Tab::setInactive() {
  active = false;
  tabButton->setLabelColor(Colors::DARK_GRAY);
  tabButton->setBackgroundColor(Colors::LIGHT_GRAY);
}

//--------------------------------------------------------------

bool Tab::isActive() {
  return active;
}

//--------------------------------------------------------------

void Tab::update() {
  tabButton->update();
}

//--------------------------------------------------------------

void Tab::draw() {
  tabButton->draw();
}

