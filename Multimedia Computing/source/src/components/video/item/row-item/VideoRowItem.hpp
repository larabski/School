#ifndef VideoRowItem_hpp
#define VideoRowItem_hpp

#include <stdio.h>
#include "Bounds.h"
#include "ofxDatGui.h"
#include "Dimensions.h"
#include "Events.hpp"
#include "Metadata.hpp"
#include "XMLFileAgent.hpp"

class VideoRowItem {

public:
  
  /**
   Takes in and a metadata object (that was previously read from an XML file).
   */
  VideoRowItem(Metadata);
  
  void update();
  void draw();
  
  void setBounds(Bounds);
  void setupPositioningButtons();
  void setHovered(bool);
  Metadata getMetadata();
  
  void onLeftButtonClicked(ofxDatGuiButtonEvent event);
  void onRightButtonClicked(ofxDatGuiButtonEvent event);
  
private:
  
  ofxDatGuiButton *moveLeftButton;
  ofxDatGuiButton *moveRightButton;
  
  Bounds bounds;
  
  /**
   The thumbnail of the video.
   */
  ofImage thumbnail;
  
  /**
   Each video will have associated a Metadata object, read from a XML file.
   */
  Metadata metadata;
  
  bool isHovered;
  
};

#endif /* VideoTimelineItem_hpp */
