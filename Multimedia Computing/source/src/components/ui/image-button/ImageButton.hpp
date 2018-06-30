#ifndef ImageButton_hpp
#define ImageButton_hpp

#include <stdio.h>
#include <string>
#include "ofxDatGui.h"
#include "Colors.h"
#include "Dimensions.h"
#include "ImageButtonProps.h"

class ImageButton {
  
public:
  
  ImageButton(std::string, ImageButtonProps);
  
  template<typename T, typename args, class ListenerClass>
  void onButtonEvent(T* owner, void (ListenerClass::*listenerMethod)(args)){
    button->onButtonEvent(owner, listenerMethod);
  }
  
  void update();
  void draw();
  void attachToEvent(ofEvent<void> event);
  void onImageButtonClicked(ofxDatGuiButtonEvent event);
  void setupButton(int backgroundColor, int backgroundColorMouseOver, int backgroundColorMouseDown, float opacity);
  
  int getX();
  int getY();
  int getWidth();
  int getHeight();
  
private:
  
  ImageButtonProps props;
  ofxDatGuiButton *button;
  ofImage image;
  ofEvent<void> attachedEvent;
  
};

#endif

