//
//  VideoRow.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 17/05/2018.
//

#ifndef VideoRow_hpp
#define VideoRow_hpp

#include <stdio.h>
#include <string.h>
#include "Dimensions.h"
#include "Events.hpp"
#include "Metadata.hpp"
#include "VideoRowItem.hpp"

class VideoRow {
  
public:
  
  /**
   Empty constructor (for when the timeline is empty).
   */
  VideoRow();
  
  /**
   Constructor that takes in an array of Metadata objects and will call #setupRow and #computeItemBounds.
   */
  VideoRow(vector<Metadata>);
  
  void update();
  void draw();
  
  vector<string> getVideoNames();
  
private:
  
  vector<VideoRowItem> videos;
  
  const int width = Dimensions::WINDOW_WIDTH;
  const int height = 200;
  const int x = 0;
  const int y = Dimensions::WINDOW_HEIGHT - height;
  const Bounds bounds = { x, y, width, height };
  
  const int GAP = Dimensions::UI_PANEL_PADDING;
  const int NUM_ITEMS = 6;
  const int ITEM_WIDTH = (width - (NUM_ITEMS + 1) * GAP) / NUM_ITEMS;
  
  void setupRow(vector<Metadata> videoMetadatas);
  void computeItemBounds();
  int getIndexByName(string);
  
  // Event Listeners.
  void onClipRemoved(Metadata &metadata);
  void onClipHovered(Metadata &metadata);
  void onClipLeftButtonClicked(Metadata &metadata);
  void onClipRightButtonClicked(Metadata &metadata);
  
};

#endif /* VideoRow_hpp */
