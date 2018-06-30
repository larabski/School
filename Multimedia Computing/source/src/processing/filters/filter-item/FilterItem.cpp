//
//  FilterItem.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 17/05/2018.
//

#include "FilterItem.hpp"

//--------------------------------------------------------------

FilterItem::FilterItem(ofxDatGuiComponent *component, bool initiallyToggled, int x, int y, bool isDropDown, string label) {
  this->x = x;
  this->y = y;
  this->isDropDown = isDropDown;
  this->component = component;
  this->toggle = new ofxDatGuiButton("");
  this->enabled = initiallyToggled;
  
  this->toggle->setWidth(Dimensions::TAB_HEIGHT, 0);
  this->toggle->setPosition(x, y);
  this->toggle->setStripeVisible(false);
  this->toggle->setBackgroundColor(enabled ? ofColor(119, 221, 119) : ofColor(221, 119, 119));
  this->toggle->setBackgroundColorOnMouseOver(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
  this->toggle->setBackgroundColorOnMouseDown(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
  this->toggle->onButtonEvent(this, &FilterItem::toggleEnabled);
  
  int componentWidth = Dimensions::NUM_SMALL_TABS * Dimensions::SMALL_TAB_WIDTH - 2 * Dimensions::UI_PANEL_PADDING - toggle->getWidth() - 5;
  this->component->setTheme(new ofxDatGuiThemeWireframe());
  
  if (!isDropDown) {
    this->component->setPosition(x + toggle->getWidth() + 5, y);
    this->component->setWidth(componentWidth, 150);
  } else {
    this->component->setPosition(x + toggle->getWidth() + 5 + 150, y);
    this->component->setWidth(115, 0);
    this->component->setBackgroundColor(ofColor(233, 233, 233));
  }
}

//--------------------------------------------------------------

void FilterItem::toggleEnabled(ofxDatGuiButtonEvent event) {
  this->enabled = !this->enabled;
  this->toggle->setBackgroundColor(enabled ? ofColor(119, 221, 119) : ofColor(221, 119, 119));
  this->toggle->setBackgroundColorOnMouseOver(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
  this->toggle->setBackgroundColorOnMouseDown(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
}

//--------------------------------------------------------------

void FilterItem::update() {
  toggle->update();
  component->update();
}

//--------------------------------------------------------------

void FilterItem::draw() {
  if (isDropDown) {
    ofSetColor(252, 250, 253);
    ofDrawRectangle(x + toggle->getWidth() + 5, y, 267, toggle->getHeight());
    ofSetColor(145, 145, 145);
    ofxDatGuiLabel *label = new ofxDatGuiLabel("Texture");
    label->setPosition(x + toggle->getWidth() + 5, y);
    label->setStripeVisible(false);
    label->setBackgroundColor(ofColor(252,250,253));
    label->setLabelColor(ofColor(110,110,110));
    label->setWidth(150);
    label->draw();
  }
  toggle->draw();
  component->draw();
}

//--------------------------------------------------------------

bool FilterItem::isEnabled() {
  return this->enabled;
}

//--------------------------------------------------------------

ofxDatGuiComponent *FilterItem::getComponent() {
  return this->component;
}
