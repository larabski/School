#ifndef TimelineSection_hpp
#define TimelineSection_hpp

#include <stdio.h>

#include "Colors.h"
#include "Section.h"
#include "ofxDatGui.h"
#include "Dimensions.h"
#include "Events.hpp"
#include "Metadata.hpp"
#include "VideoRow.hpp"

class TimelineSection : public Section {
  
public:
  
  void setup();
  void update();
  void draw();
  
private:
  
  ofxDatGuiDropdown *transitionsDropdown;
  ofxDatGuiButton *playButton;
  VideoRow *videoRow;
  
  const int width = Dimensions::WINDOW_WIDTH;
  const int height = 200;
  const int x = 0;
  const int y = Dimensions::WINDOW_HEIGHT - height;
  const Bounds bounds = { x, y, width, height };
  
  void setupPlayButton();
  void setupTransitionsDropdown();
  void buildTimelineFromMetadatas(vector<Metadata> &metadatas);
  
  // Event Listeners.
  void onPlayButtonClicked(ofxDatGuiButtonEvent event);
  
};

#endif /* TimelineSection_hpp */
