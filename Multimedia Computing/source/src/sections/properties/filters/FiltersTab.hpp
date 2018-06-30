#ifndef FiltersTab_hpp
#define FiltersTab_hpp

#include <stdio.h>
#include "Tab.hpp"
#include "Events.hpp"
#include "Filters.hpp"
#include "Metadata.hpp"
#include "FilterItem.hpp"
#include "XMLFileAgent.hpp"
#include "ImportableFilterItem.hpp"
#include "TimeFormater.h"
#include "Colors.h"
#include "ofxDatGui.h"
#include "Dimensions.h"

class FiltersTab {
  
public:
  
  FiltersTab(std::string, int, int);
  
  void update();
  void draw();
  void setActive();
  void setInactive();
  void attachToEvent(ofEvent<void> event);
  
private:
  
  Tab *tab;
  ofxDatGuiButton *applyFiltersButton;
  
  FilterItem *fromDateFilter;
  FilterItem *untilDateFilter;
  FilterItem *luminanceFilter;
  FilterItem *colorRFilter;
  FilterItem *colorGFilter;
  FilterItem *colorBFilter;
  FilterItem *edgeDistributionFilter;
  FilterItem *numberOfFacesFilter;
  FilterItem *textureFilter;
  FilterItem *rythmFilter;
  
  ImportableFilterItem *numTimesObjectAppearsFilter;
  
  /**
   It's useful to keep a reference to the the filters that were last applied,
   so that spamming the "Apply Filters" button doesn't do redundant computing.
   */
  Filters lastAppliedFilters;
  
  void setupFiltersGui();
  void setupApplyButton();
  void notifyFiltersApplied(ofxDatGuiButtonEvent event);

  /**
   Build and return a Metadata (filters) object based on current values.
   */
  Filters generateAppliedFiltersObject();
  
};

#endif /* FiltersTab_hpp */
