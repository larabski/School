#include "VideoSettingsTab.hpp"

//--------------------------------------------------------------

VideoSettingsTab::VideoSettingsTab(string label, int x, int y) {
  tab = new Tab(label, x, y, false);
  videoSelected = false;
  tab->setInactive();
}

//--------------------------------------------------------------

void VideoSettingsTab::setupGuiForVideoMetadata() {
  infoLabels.clear();
  
  ofxDatGuiLabel *nameLabel = new ofxDatGuiLabel("Name: " + videoMetadata.getName());
  infoLabels.push_back(nameLabel);
  
  ofxDatGuiLabel *dateLabel = new ofxDatGuiLabel("Date: " + videoMetadata.getDate());
  infoLabels.push_back(dateLabel);
  
  ofxDatGuiLabel *luminanceLabel = new ofxDatGuiLabel("Luminance: " + videoMetadata.getLuminance());
  infoLabels.push_back(luminanceLabel);
  
  ofxDatGuiLabel *colorRLabel = new ofxDatGuiLabel("Color (R): " + videoMetadata.getColorR());
  infoLabels.push_back(colorRLabel);
  
  ofxDatGuiLabel *colorGLabel = new ofxDatGuiLabel("Color (G): " + videoMetadata.getColorG());
  infoLabels.push_back(colorGLabel);
  
  ofxDatGuiLabel *colorBLabel = new ofxDatGuiLabel("Color (B): " + videoMetadata.getColorB());
  infoLabels.push_back(colorBLabel);
  
  ofxDatGuiLabel *edgeDistributionLabel = new ofxDatGuiLabel("Edge Dist: " + videoMetadata.getEdgeDistribution());
  infoLabels.push_back(edgeDistributionLabel);
  
  ofxDatGuiLabel *numFacesLabel = new ofxDatGuiLabel("Nº Faces: " + videoMetadata.getNumberFaces());
  infoLabels.push_back(numFacesLabel);
  
  ofxDatGuiLabel *textureLabel = new ofxDatGuiLabel("Texture: " + videoMetadata.getTexture());
  infoLabels.push_back(textureLabel);
  
  ofxDatGuiLabel *rythmLabel = new ofxDatGuiLabel("Rythm: " + videoMetadata.getRythm());
  infoLabels.push_back(rythmLabel);
  
  // ---
  
  ofxDatGuiTheme wireframeTheme = ofxDatGuiThemeWireframe();
  const int BASE_X = Dimensions::UI_PANEL_PADDING;
  const int BASE_Y = Dimensions::TAB_HEIGHT + Dimensions::UI_PANEL_PADDING;
  
  for (int i = 0; i < infoLabels.size(); i++) {
    infoLabels[i]->setTheme(&wireframeTheme);
    infoLabels[i]->setPosition(BASE_X, BASE_Y + (30 * i));
    infoLabels[i]->setWidth(Dimensions::NUM_SMALL_TABS * Dimensions::SMALL_TAB_WIDTH - 2 * Dimensions::UI_PANEL_PADDING);
  }
}

//--------------------------------------------------------------

void VideoSettingsTab::update() {
  tab->update();
  if (tab->isActive() && videoSelected) {
    for (int i = 0; i < infoLabels.size(); i++) {
      infoLabels[i]->update();
    }
  }
}

//--------------------------------------------------------------

void VideoSettingsTab::draw() {
  tab->draw();
  if (!tab->isActive()) return;
  if (videoSelected) {
    for (int i = 0; i < infoLabels.size(); i++) {
      infoLabels[i]->draw();
    }
  } else {
    ofSetHexColor(Colors::CHARCOAL_GRAY);
    ofDrawBitmapString("No Video Selected.", 95, 235);
  }
}

//--------------------------------------------------------------

void VideoSettingsTab::attachToEvent(ofEvent<void> tabClickEvent) {
  tab->attachToEvent(tabClickEvent);
}

//--------------------------------------------------------------

void VideoSettingsTab::setActive() {
  videoSelected = false;
  tab->setActive();
}

//--------------------------------------------------------------

void VideoSettingsTab::setActive(Metadata metadata) {
  this->videoSelected = true;
  tab->setActive();
  if (metadata.getName() == videoMetadata.getName()) return;
  this->videoMetadata = metadata;
  setupGuiForVideoMetadata();
}

//--------------------------------------------------------------

void VideoSettingsTab::setInactive() {
  tab->setInactive();
}
