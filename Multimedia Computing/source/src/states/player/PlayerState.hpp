#ifndef PlayerState_hpp
#define PlayerState_hpp

#include <stdio.h>
#include "State.h"
#include "PlayerSection.hpp"
#include "Dimensions.h"
#include "Colors.h"


class PlayerState : public State {
  
public:
  
  void setup();
  void update();
  void draw();
  
private:
  
  PlayerSection playerSection;
  
};


#endif /* PlayerState_hpp */
