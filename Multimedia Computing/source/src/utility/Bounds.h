#ifndef Bounds_h
#define Bounds_h

#include "ofMain.h"

struct Bounds {
  int x;
  int y;
  int width;
  int height;
  
  bool containsMouse() {
    const int mouseX = ofGetMouseX();
    const int mouseY = ofGetMouseY();
    return (mouseX >= x && mouseX <= x + width) && (mouseY >= y && mouseY <= y + height);
  }
  
  bool isMouseInBoxArea(int x, int y, int width, int height){
    const int mouseX = ofGetMouseX();
    const int mouseY = ofGetMouseY();
    return ((mouseX >= x && mouseX <= x + width) && (mouseY >= y && mouseY <= y + height));
  }
};

#endif /* Bounds_h */
