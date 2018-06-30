#ifndef VideoGrid_hpp
#define VideoGrid_hpp

#include <stdio.h>
#include "Bounds.h"
#include "Colors.h"
#include "Dimensions.h"
#include "Metadata.hpp"
#include "XMLFileAgent.hpp"
#include "VideoGridItem.hpp"

class VideoGrid {
  
public:
  
  /**
   Empty constructor to use for the Timeline Clips tab (no clips shown when the
   app is first launched.
   */
  VideoGrid(string);
  
  /**
   Constructor takes in (vector<Metadata>, sectionName). The display in rows/columns
   is computed implicitly.
   */
  VideoGrid(vector<Metadata>, string);

  void update();
  void draw();
  
  bool isEmpty();
  
private:

  const int GAP = 30;
  const int NUM_COLUMNS = 3;
  const int ITEM_HEIGHT = 155;
  
  const int width = Dimensions::VIDEO_SECTION_WIDTH;
  const int height = 444 - Dimensions::TAB_HEIGHT;
  const int x = Dimensions::PROPERTIES_SECTION_WIDTH;
  const int y = Dimensions::TAB_HEIGHT;
  const Bounds bounds = { x, y, width, height };

  /**
   A VideoGrid will have a bunch of VideoGridItems.
   */
  vector<VideoGridItem> videos;
  
  string sectionName;
  
  void setupGrid(vector<Metadata>);
  void computeItemBounds();
  int getIndexByName(string);
  
  // Event Listeners.
  void onClipImported(Metadata &metadata);
  void onClipHovered(Metadata &metadata);
  void onClipRemoved(Metadata &metadata);
  
};

#endif /* VideoGrid_hpp */
