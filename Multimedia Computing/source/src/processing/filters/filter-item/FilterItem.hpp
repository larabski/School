//
//  FilterItem.hpp
//  Project-CM
//
//  Created by Francisco Cunha on 17/05/2018.
//

#ifndef FilterItem_hpp
#define FilterItem_hpp

#include <stdio.h>
#include "Colors.h"
#include "ofxDatGui.h"
#include "Dimensions.h"

class FilterItem {

public:
  
  /**
   Takes in the desired component, a bool indicating whether or not the filter should be toggled by default and two integers, X and Y.
   */
  FilterItem(ofxDatGuiComponent*, bool, int, int, bool, string);
  
  void update();
  void draw();
  
  bool isEnabled();
  void toggleEnabled(ofxDatGuiButtonEvent event);
  ofxDatGuiComponent *getComponent();
  
private:
  
  int x;
  int y;
  bool isDropDown;
  bool enabled;
  ofxDatGuiButton *toggle;
  ofxDatGuiComponent *component;
  
};

#endif /* FilterItem_hpp */
