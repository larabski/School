//
//  ImportableFilterItem.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 27/05/2018.
//

#include "ImportableFilterItem.hpp"

//--------------------------------------------------------------

ImportableFilterItem::ImportableFilterItem(ofxDatGuiComponent *component, bool initiallyToggled, int x, int y) {
  this->x = x;
  this->y = y;
  this->component = component;
  this->toggle = new ofxDatGuiButton("");
  this->enabled = initiallyToggled;
  this->fileName = NO_FILE;
  setupToggle();
  setupImportImageButton();
  setupComponent();
}

//--------------------------------------------------------------

void ImportableFilterItem::setupToggle() {
  this->toggle->setWidth(Dimensions::TAB_HEIGHT, 0);
  this->toggle->setPosition(x, y);
  this->toggle->setStripeVisible(false);
  this->toggle->setBackgroundColor(enabled ? ofColor(119, 221, 119) : ofColor(221, 119, 119));
  this->toggle->setBackgroundColorOnMouseOver(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
  this->toggle->setBackgroundColorOnMouseDown(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
  this->toggle->onButtonEvent(this, &ImportableFilterItem::toggleEnabled);
}

//--------------------------------------------------------------

void ImportableFilterItem::setupImportImageButton() {
  this->importImageButton = new ofxDatGuiButton(":: NO FILE ::");
  this->importImageButton->setPosition(x + toggle->getWidth() + 5, y);
    this->importImageButton->setTheme(new ofxDatGuiThemeWireframe());
  this->importImageButton->setWidth(95);
  this->importImageButton->setLabelAlignment(ofxDatGuiAlignment::LEFT);
  this->importImageButton->onButtonEvent(this, &ImportableFilterItem::importClicked);
}

//--------------------------------------------------------------

void ImportableFilterItem::setupComponent() {
  this->component->setPosition(importImageButton->getX() + importImageButton->getWidth() + 5, y);
  this->component->setBackgroundColor(ofColor(252, 250, 15));
  this->component->setTheme(new ofxDatGuiThemeWireframe());
  int componentWidth = Dimensions::NUM_SMALL_TABS * Dimensions::SMALL_TAB_WIDTH - 2 * Dimensions::UI_PANEL_PADDING - toggle->getWidth() - 5 - importImageButton->getWidth() - 5;
  this->component->setWidth(componentWidth, 50);
}

//--------------------------------------------------------------

void ImportableFilterItem::toggleEnabled(ofxDatGuiButtonEvent event) {
  if (fileName == NO_FILE) return;
  this->enabled = !this->enabled;
  this->toggle->setBackgroundColor(enabled ? ofColor(119, 221, 119) : ofColor(221, 119, 119));
  this->toggle->setBackgroundColorOnMouseOver(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
  this->toggle->setBackgroundColorOnMouseDown(enabled ? ofColor(79, 153, 79) : ofColor(153, 79, 79));
}

//--------------------------------------------------------------

void ImportableFilterItem::importClicked(ofxDatGuiButtonEvent event) {
  ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an image file");
  if (!openFileResult.bSuccess) return;
  
  ofFile imageFile(openFileResult.getPath());
  if (!imageFile.exists()) return;
  
  string fileExtension = ofToUpper(imageFile.getExtension());
  if (fileExtension == "PNG" || fileExtension == "JPG" || fileExtension == "JPEG") {
    string openedFileName = openFileResult.getName();
    int MAX_NAME_LENGTH = 12;
    string trimmedFileName = openedFileName.length() > MAX_NAME_LENGTH
      ? "..." + openedFileName.substr(openedFileName.length() - 10, openedFileName.length())
      : openedFileName;
    this->filePath = openFileResult.getPath();
    this->fileName = trimmedFileName;
    this->importImageButton->setLabel(trimmedFileName);
  }
}

//--------------------------------------------------------------

std::string ImportableFilterItem::getFilePath() {
  return this->filePath;
}

//--------------------------------------------------------------

void ImportableFilterItem::update() {
  toggle->update();
  importImageButton->update();
  component->update();
}

//--------------------------------------------------------------

void ImportableFilterItem::draw() {
  toggle->draw();
  importImageButton->draw();
  component->draw();
}

//--------------------------------------------------------------

bool ImportableFilterItem::isEnabled() {
  return this->enabled;
}

//--------------------------------------------------------------

ofxDatGuiComponent *ImportableFilterItem::getComponent() {
  return this->component;
}
