#ifndef TimelineClipsTab_hpp
#define TimelineClipsTab_hpp

#include <stdio.h>
#include "Tab.hpp"
#include "Events.hpp"
#include "Metadata.hpp"
#include "VideoGrid.hpp"

class TimelineClipsTab {
  
public:
  
  TimelineClipsTab(std::string, int, int);
  
  void update();
  void draw();
  void setActive();
  void setInactive();
  void attachToEvent(ofEvent<void> event);
  void buildGridFromMetadatas(vector<Metadata> &videoMetadatas);
  
private:
  
  Tab *tab;
  VideoGrid *videoGrid;
  
};

#endif /* TimelineClipsTab_hpp */
