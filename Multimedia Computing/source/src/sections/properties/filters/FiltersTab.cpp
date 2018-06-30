#include "FiltersTab.hpp"

//--------------------------------------------------------------

FiltersTab::FiltersTab(string label, int x, int y) {
  tab = new Tab(label, x, y, false);
  tab->setActive();
  setupFiltersGui();
  setupApplyButton();
}

//--------------------------------------------------------------

void FiltersTab::setupFiltersGui() {
  const int BASE_X = Dimensions::UI_PANEL_PADDING;
  const int BASE_Y = Dimensions::TAB_HEIGHT + Dimensions::UI_PANEL_PADDING;
  
  TimeFormater timeFormater;
  string day = timeFormater.formatWithTwoDecimalNumbers(ofGetDay());
  string month = timeFormater.formatWithTwoDecimalNumbers(ofGetMonth());
  string year = timeFormater.formatWithTwoDecimalNumbers(ofGetYear());
  string todayDate = day + "/" + month + "/" + year;
  
  ofxDatGuiTextInput *fromDateInput = new ofxDatGuiTextInput("Date (from)", todayDate);
  fromDateFilter = new FilterItem(fromDateInput, false, BASE_X, BASE_Y, false, "");
  
  ofxDatGuiTextInput *untilDateInput = new ofxDatGuiTextInput("Date (until)", todayDate);
  untilDateFilter = new FilterItem(untilDateInput, false, BASE_X, BASE_Y + 30, false, "");
  
  ofxDatGuiSlider *luminanceSlider = new ofxDatGuiSlider("Luminance  ( ± 20 )", 0, 255, 100);
  luminanceSlider->setPrecision(0);
  luminanceFilter = new FilterItem(luminanceSlider, true, BASE_X, BASE_Y + 60, false, "");
  
  // TODO: A Toggle just for the "Color"?
  
  ofxDatGuiSlider *colorRSlider = new ofxDatGuiSlider("R ( ± 20 )", 0, 255, 50);
  colorRSlider->setPrecision(0);
  colorRFilter = new FilterItem(colorRSlider, false, BASE_X, BASE_Y + 90, false, "");
  
  ofxDatGuiSlider *colorGSlider = new ofxDatGuiSlider("G ( ± 20 )", 0, 255, 100);
  colorGSlider->setPrecision(0);
  colorGFilter = new FilterItem(colorGSlider, false, BASE_X, BASE_Y + 120, false, "");
  
  ofxDatGuiSlider *colorBSlider = new ofxDatGuiSlider("B ( ± 20 )", 0, 255, 75);
  colorBSlider->setPrecision(0);
  colorBFilter = new FilterItem(colorBSlider, false, BASE_X, BASE_Y + 150, false, "");
  
  ofxDatGuiSlider *edgeDistributionInput = new ofxDatGuiSlider("Vertical Edge % ( ± 10% )", 0, 100, 50);
  edgeDistributionInput->setPrecision(0);
  edgeDistributionFilter = new FilterItem(edgeDistributionInput, false, BASE_X, BASE_Y + 180, false, "");
  
  ofxDatGuiSlider *numberOfFacesSlider = new ofxDatGuiSlider("Nº of Faces ( ± 1 )", 0, 25, 2);
  numberOfFacesSlider->setPrecision(0);
  numberOfFacesFilter = new FilterItem(numberOfFacesSlider, false, BASE_X, BASE_Y + 210, false, "");
  
  vector<string> options = { "Low  \"<=5\"", "Medium  \"<=10\"", "High  \">10\"" };
  ofxDatGuiDropdown *texturesInput = new ofxDatGuiDropdown("", options);
  texturesInput->setStripeVisible(false);
  texturesInput->collapse();
  texturesInput->select(0);
  textureFilter = new FilterItem(texturesInput, false, BASE_X, BASE_Y + 240, true, "Texture");
  
  ofxDatGuiSlider *rythmSlider = new ofxDatGuiSlider("Rythm ( ± 0.15 )", 0, 5, 0.2);
  rythmFilter = new FilterItem(rythmSlider, false, BASE_X, BASE_Y + 270, false, "");
  
  ofxDatGuiSlider *numTimesObjectAppearsSlider = new ofxDatGuiSlider("Nº ( ± 1 )", 0, 100, 5);
  numTimesObjectAppearsSlider->setPrecision(0);
  numTimesObjectAppearsFilter = new ImportableFilterItem(numTimesObjectAppearsSlider, false, BASE_X, BASE_Y + 300);
}

//--------------------------------------------------------------

void FiltersTab::setupApplyButton() {
  applyFiltersButton = new ofxDatGuiButton("Apply Filters");
  applyFiltersButton->setLabelAlignment(ofxDatGuiAlignment::CENTER);
  applyFiltersButton->setLabelColor(Colors::WHITE);
  applyFiltersButton->setBackgroundColors(ofColor(28, 183, 255), ofColor(0, 105, 170), ofColor(0, 59, 118));
  applyFiltersButton->setStripeVisible(false);
  applyFiltersButton->setWidth(Dimensions::NUM_SMALL_TABS * Dimensions::SMALL_TAB_WIDTH - 30);

  const int x = Dimensions::UI_PANEL_PADDING;
  const int y = Dimensions::PROPERTIES_SECTION_HEIGHT - Dimensions::UI_PANEL_PADDING - Dimensions::TAB_HEIGHT;
  applyFiltersButton->setPosition(x, y);
  
  applyFiltersButton->onButtonEvent(this, &FiltersTab::notifyFiltersApplied);
}

//--------------------------------------------------------------

void FiltersTab::notifyFiltersApplied(ofxDatGuiButtonEvent event) {
  /**
   Build Filters object based on current values.
   */
  Filters mostRecentFiltersApplied = generateAppliedFiltersObject();
  this->lastAppliedFilters = mostRecentFiltersApplied;
  /**
   Calculate which videos pass the criteria test.
   */
  vector<Metadata> allVideosMetadatas = XMLFileAgent().loadMetadataForAllVideos();
  vector<Metadata> filteredVideoMetadatas;

  for (int i = 0; i < allVideosMetadatas.size(); i++) {
    Metadata videoMetadata = allVideosMetadatas[i];
    if (mostRecentFiltersApplied.acceptsVideo(videoMetadata)) {
      filteredVideoMetadatas.push_back(videoMetadata);
    }
  }
  /**
   Notify the change, with the acceptable videos attached.
   */
  ofNotifyEvent(Events::filtersAppliedEvent, filteredVideoMetadatas, this);
}

//--------------------------------------------------------------

Filters FiltersTab::generateAppliedFiltersObject() {
  Filters newFiltersApplied = Filters();
  
  // Date
  
  ofxDatGuiTextInput *castedFromDate = (ofxDatGuiTextInput*) fromDateFilter->getComponent();
  newFiltersApplied.setFromDate(fromDateFilter->isEnabled() ? castedFromDate->getText() : "DISABLED");
  
  ofxDatGuiTextInput *castedUntilDate = (ofxDatGuiTextInput*) untilDateFilter->getComponent();
  newFiltersApplied.setUntilDate(untilDateFilter->isEnabled() ? castedUntilDate->getText() : "DISABLED");
  
  // Luminance
  
  ofxDatGuiSlider *castedLuminance = (ofxDatGuiSlider*) luminanceFilter->getComponent();
  newFiltersApplied.setLuminance(luminanceFilter->isEnabled() ? std::to_string(castedLuminance->getValue()) : "DISABLED");
  
  // Color (RGB)
  
  ofxDatGuiSlider *castedColorR = (ofxDatGuiSlider*) colorRFilter->getComponent();
  ofxDatGuiSlider *castedColorG = (ofxDatGuiSlider*) colorGFilter->getComponent();
  ofxDatGuiSlider *castedColorB = (ofxDatGuiSlider*) colorBFilter->getComponent();
  
  const string red = std::to_string(castedColorR->getValue());
  newFiltersApplied.setColorR(colorRFilter->isEnabled() ? red : "DISABLED");
  
  const string green = std::to_string(castedColorG->getValue());
  newFiltersApplied.setColorG(colorGFilter->isEnabled() ? green : "DISABLED");
  
  const string blue = std::to_string(castedColorB->getValue());
  newFiltersApplied.setColorB(colorBFilter->isEnabled() ? blue : "DISABLED");

  // Edge Distribution
  
  ofxDatGuiSlider *castedEdgeDist = (ofxDatGuiSlider*) edgeDistributionFilter->getComponent();
  newFiltersApplied.setEdgeDistribution(edgeDistributionFilter->isEnabled() ? std::to_string(castedEdgeDist->getValue()) : "DISABLED");
  
  // Number of Faces
  
  ofxDatGuiSlider *castedNumberOfFaces = (ofxDatGuiSlider*) numberOfFacesFilter->getComponent();
  newFiltersApplied.setNumberFaces(numberOfFacesFilter->isEnabled() ? std::to_string(castedNumberOfFaces->getValue()) : "DISABLED");
  
  // Texture
  
  ofxDatGuiDropdown *castedTexture = (ofxDatGuiDropdown*) textureFilter->getComponent();
  newFiltersApplied.setTexture(textureFilter->isEnabled() ? castedTexture->getSelected()->getLabel() : "DISABLED");
  
  // Rythm
  
  ofxDatGuiSlider *castedRythm = (ofxDatGuiSlider*) rythmFilter->getComponent();
  newFiltersApplied.setRythm(rythmFilter->isEnabled() ? std::to_string(castedRythm->getValue()) : "DISABLED");
  
  // Number of Times a Specific Object Appears in the Video
  
  ofxDatGuiSlider *castedNumberOfTimes = (ofxDatGuiSlider*) numTimesObjectAppearsFilter->getComponent();
  string imagePath = numTimesObjectAppearsFilter->isEnabled() ? numTimesObjectAppearsFilter->getFilePath() : "DISABLED";
  int numTimes = (int) castedNumberOfTimes->getValue();
  newFiltersApplied.setTargetNumTimesObjectAppears(imagePath, numTimes);
  
  return newFiltersApplied;
}

//--------------------------------------------------------------

void FiltersTab::update() {
  tab->update();
  if (!tab->isActive()) return;
  
  fromDateFilter->update();
  untilDateFilter->update();
  luminanceFilter->update();
  colorRFilter->update();
  colorGFilter->update();
  colorBFilter->update();
  edgeDistributionFilter->update();
  numberOfFacesFilter->update();
  textureFilter->update();
  rythmFilter->update();
  numTimesObjectAppearsFilter->update();
  
  applyFiltersButton->update();
}

//--------------------------------------------------------------

void FiltersTab::draw() {
  tab->draw();
  if (!tab->isActive()) return;
  
  fromDateFilter->draw();
  untilDateFilter->draw();
  luminanceFilter->draw();
  colorRFilter->draw();
  colorGFilter->draw();
  colorBFilter->draw();
  edgeDistributionFilter->draw();
  numberOfFacesFilter->draw();
  rythmFilter->draw();
  numTimesObjectAppearsFilter->draw();
  textureFilter->draw();
  applyFiltersButton->draw();
}

//--------------------------------------------------------------

void FiltersTab::attachToEvent(ofEvent<void> tabClickEvent) {
  tab->attachToEvent(tabClickEvent);
}

//--------------------------------------------------------------

void FiltersTab::setActive() {
  tab->setActive();
}

//--------------------------------------------------------------

void FiltersTab::setInactive() {
  tab->setInactive();
}
