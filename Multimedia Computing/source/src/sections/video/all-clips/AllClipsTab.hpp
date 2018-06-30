#ifndef AllClipsTab_hpp
#define AllClipsTab_hpp

#include <stdio.h>

#include "Tab.hpp"
#include "Metadata.hpp"
#include "XMLFileAgent.hpp"
#include "VideoGrid.hpp"

class AllClipsTab {
  
public:
  
  AllClipsTab(std::string, int, int);
  
  void update();
  void draw();
  void setActive();
  void setInactive();
  void attachToEvent(ofEvent<void> event);
  
private:
  
  Tab *tab;
  VideoGrid *videoGrid;
  
};

#endif /* AllClipsTab_hpp */
