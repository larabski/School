#ifndef MainState_hpp
#define MainState_hpp

#include <stdio.h>
#include "State.h"
#include "Colors.h"
#include "Dimensions.h"
#include "TimelineSection.hpp"
#include "VideoSection.hpp"
#include "PropertiesSection.hpp"

class MainState : public State {

public:
  
  void setup();
  void update();
  void draw();
  
private:
  
  TimelineSection timelineSection;
  VideoSection videoSection;
  PropertiesSection propertiesSection;
  
};

#endif /* MainState_hpp */
