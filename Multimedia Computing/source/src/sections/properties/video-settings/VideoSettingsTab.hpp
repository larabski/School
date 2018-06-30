#ifndef VideoSettingsTab_hpp
#define VideoSettingsTab_hpp

#include <stdio.h>
#include "Dimensions.h"
#include "Tab.hpp"
#include "Metadata.hpp"
#include "ofxDatGui.h"

class VideoSettingsTab {
  
public:
  
  VideoSettingsTab(std::string, int, int);
  
  void update();
  void draw();
  void setActive();
  void setActive(Metadata);
  void setInactive();
  void attachToEvent(ofEvent<void> event);
  
private:
  
  Tab *tab;
  vector<ofxDatGuiLabel*> infoLabels;
  Metadata videoMetadata;
  
  bool videoSelected;
  
  void setupGuiForVideoMetadata();

};

#endif /* VideoSettingsTab_hpp */
