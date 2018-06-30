#ifndef VideoSection_hpp
#define VideoSection_hpp

#include <stdio.h>

#include "Section.h"
#include "Bounds.h"
#include "Colors.h"
#include "Events.hpp"
#include "Dimensions.h"
#include "ImageButton.hpp"
#include "AllClipsTab.hpp"
#include "TimelineClipsTab.hpp"
#include "LoadVideoButton.hpp"
#include "ImageButtonProps.h"

class VideoSection : public Section {
  
public:
  
  void setup();
  void update();
  void draw();
    
  void onAllClipsTabClicked();
  void onTimelineClipsTabClicked();
  void onLoadVideoButtonClicked();
  
private:
  
  const int width = Dimensions::VIDEO_SECTION_WIDTH;
  const int height = 444;
  const int x = Dimensions::PROPERTIES_SECTION_WIDTH;
  const int y = 0;
  
  const string ALL_CLIPS_TAB_LABEL = "All Clips";
  const string TIMELINE_CLIPS_TAB_LABEL = "Timeline Clips";
  const string BUTTON_IMAGE_PATH = "images/folder.png";
  
  const Bounds bounds = { x, y, width, height };
  
  AllClipsTab *allClipsTab;
  TimelineClipsTab *timelineClipsTab;
  LoadVideoButton *loadVideoButton;

};

#endif /* VideoSection_hpp */
