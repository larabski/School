#ifndef VideoGridItem_hpp
#define VideoGridItem_hpp

#include <stdio.h>
#include <string.h>
#include "Bounds.h"
#include "Colors.h"
#include "Dimensions.h"
#include "ofxDatGuiButton.h"
#include "ofxDatGuiLabel.h"
#include "Events.hpp"
#include "Metadata.hpp"
#include "ImageButton.hpp"
#include "XMLFileAgent.hpp"

class VideoGridItem {
  
public:
  
  /**
   Takes in and a metadata object (that was previously read from an XML file).
   */
  VideoGridItem(Metadata, std::string);
  
  void update();
  void draw();
  
  /**
   Setting each item's bounds is a task that is delegated to the Grid itself.
   This is also true for the other setup methods: one can only setup the position
   of the label and removeButton after the bounds have been set.
   */
  void setBounds(Bounds);
  void setupTitleLabel();
  void setupRemoveButton();
  void setupPlayButton();
  void onRemoveButtonClicked(ofxDatGuiButtonEvent event);
  void onPlayButtonClicked(ofxDatGuiButtonEvent event);
  
  Metadata getMetadata();
  void setHovered(bool);
  
private:
  
  /**
   The video's title label.
   */
  ofxDatGuiLabel *titleLabel;
  
  /**
   The button on the top-right to remove the clip from the application.
   */
  ofxDatGuiButton *removeButton;
  
  /**
   The button to play the video in the center.
   */
  ImageButton *playButton;
  
  /**
   Each VideoGridItem will have different bounds.
   -- X and Y will be based on the grid row/col.
   -- Width will be computed dynamically, based on the gap and the number of columns.
   -- Height should be the same everytime (?)
   */
  Bounds bounds;
  
  /**
   Each video will have associated a Metadata object, read from a XML file.
   */
  Metadata metadata;
  
  bool isHovered;
  
  /**
   The thumbnail of the video.
   */
  ofImage thumbnail;
  
  /**
   The video's representative frames that will be played in a loop
   whilst the video is hovered.
   */
  vector<ofImage> representativeFrames;
  
  /**
   Counter used to keep track of which representative frame to draw.
   */
  int frameLoopCounter;
  
  /**
   Defines for how long does each representative frame stays on the screen during
   the representative frames looping process. If this value is, for instance, 30, it
   means that each rep frame stays on the screen during 30 frames.
   */
  int SPOTLIGHT_TIME_PER_FRAME = 30;
  
};

#endif /* VideoGridItem_hpp */
