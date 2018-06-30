#ifndef PropertiesSection_hpp
#define PropertiesSection_hpp

#include <stdio.h>
#include "Section.h"
#include "Bounds.h"
#include "Colors.h"
#include "Events.hpp"
#include "Dimensions.h"
#include "FiltersTab.hpp"
#include "VideoSettingsTab.hpp"
#include "Metadata.hpp"

class PropertiesSection : public Section {
    
public:
  
  void setup();
  void update();
  void draw();
  
  void onFiltersButtonClicked();
  void onVideoSettingsButtonClicked();
  void onVideoSingleClicked(Metadata &metadata);
  
private:
    
  const int width = Dimensions::VIDEO_SECTION_WIDTH;
  const int height = 444;
  const int x = 0;
  const int y = 0;
  
  const string FILTERS_TAB_LABEL = "Filters";
  const string VIDEO_SETTINGS_TAB_LABEL = "Video Settings";

  const Bounds bounds = { x, y, width, height };
  
  FiltersTab *filtersTab;
  VideoSettingsTab *videoSettingsTab;

};

#endif /* PropertiesSection_hpp */
